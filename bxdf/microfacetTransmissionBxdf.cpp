#include "microfacetTransmissionBxdf.h"
#include "mathConstantDef.h"
#include <common.h>
#include <mathUtility.h>

MicrofacetTransmissionBxdf::MicrofacetTransmissionBxdf(float roughness, float etaI, float etaT)
    : Bxdf(BxdfType::TRANSMISSION | BxdfType::GLOSSY), etaI_(etaI), etaT_(etaT)
{
    roughness_ = roughness;
    // 假设 alpha 直接等于 roughness，如果 GGX 需要 alpha = roughness^2，这里需要改动
    alpha_ = roughness_; 

    if (alpha_ <= 0)
        alpha_ = MathConstant::FLOAT_SMALL_NUMBER;
}

// SampleGGX: 根据 GGX 分布采样一个微面元法线 H
// N: 宏观表面法线 (通常是局部空间的 (0,0,1))
// roughness: 表面的粗糙度参数
Vector3 MicrofacetTransmissionBxdf::SampleGGX(const Vector3& N, float roughness) const
{
    // 在 BxDF 局部空间，宏观法线 N 总是 (0,0,1)
    // 所以采样的 H 也是相对于 (0,0,1) 生成的
    float alpha = roughness; // 对应你的 alpha_

    // 1. 生成球面坐标
    float u1 = MathUtility::genRandomDecimal();
    float u2 = MathUtility::genRandomDecimal();

    float phi = MathConstant::TWO_PI * u1; // 0 到 2PI
    
    // 计算 cosThetaH
    // 这里的公式是从 PBRT v3 中 GGX 采样的倒数转换而来
    float cosThetaH = std::sqrt((1.0f - u2) / (1.0f + (alpha * alpha - 1.0f) * u2));
    float sinThetaH = std::sqrt(std::max(0.0f, 1.0f - cosThetaH * cosThetaH)); // 确保不为负

    // 2. 将球面坐标转换为标准正交基下的 H (N=(0,0,1))
    Vector3 H_local;
    H_local.x = sinThetaH * std::cos(phi);
    H_local.y = sinThetaH * std::sin(phi);
    H_local.z = cosThetaH; // cosThetaH 总是 >= 0，所以 H_local.z 总是 >= 0

    return H_local;
}

// sample_f：根据 BTDF 采样一个入射方向，并返回该方向的 BTDF 值和 PDF
// wo: 出射方向（通常是相机或当前光线方向）
// wi: 输出参数，采样的入射方向（新的光线方向）
// pdf: 输出参数，采样的概率密度函数值
Color MicrofacetTransmissionBxdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const
{
    // BxDF 在局部空间工作，表面法线 N 默认为 (0,0,1)
    // 根据重要提示，假定 wo 已经在正确的半球，不需要翻转
    Vector3 N(0.0f, 0.0f, 1.0f); // 局部空间宏观法线
    if(!N.isSameDir(wo))
    {
        N = -N;
    }
    Vector3 local_wo = wo;       // 假设 wo 已经根据 N 调整到局部空间正确半球
    Vector3 local_N = N;         // 宏观法线保持 (0,0,1)

    float cosThetaO = local_wo * local_N; // wo 和 N 的点积
    if (cosThetaO == 0.0f) {
        pdf = 0.0f;
        return Color(0.0f);
    }
    
    // --- 1. 采样微面元法线 H ---
    // SampleGGX 内部已经假定 N=(0,0,1) 并返回局部空间的 H
    Vector3 H = SampleGGX(local_N, alpha_);

    // --- 2. 根据 H 和 local_wo 计算折射方向 wi ---
    float current_etaI = etaI_; // 介质1的折射率
    float current_etaT = etaT_; // 介质2的折射率

    bool isTotalReflected = false;
    float f_refract_dummy; // 菲涅尔反射率值，这里不需要
    // (-local_wo) 是光线入射到微面元的方向
    wi = (-local_wo).refract(H, current_etaI, current_etaT, isTotalReflected, f_refract_dummy);

    // 如果发生全内反射 (TIR) 或者折射到宏观法线同一侧（不是透射）
    float cosThetaI = wi * local_N; // 采样到的 wi 与局部宏观法线 local_N 的点积
    if (isTotalReflected || cosThetaI * cosThetaO >= 0.0f) {
        pdf = 0.0f;
        return Color(0.0f);
    }
    
    // --- 3. 计算 PDF for Transmission ---
    float D_val = D(H); // NDF 值

    float H_dot_Wo = H * local_wo; // H . wo
    float H_dot_Wi = H * wi;       // H . wi

    // 计算微面元菲涅尔反射率 (F)
    // Common::fresnel 的参数为 (etaI, etaT, cosThetaI, cosThetaT)
    // 这里的 cosThetaI 和 cosThetaT 对应微面元上的入射角和透射角余弦值
    float F_val_at_H = Common::fresnel(current_etaI, current_etaT, std::abs(H_dot_Wo), std::abs(H_dot_Wi)); 
    if (F_val_at_H == 1.0f) { // 如果菲涅尔反射率为1，表示全反射
        pdf = 0.0f;
        return Color(0.0f);
    }

    // 雅可比变换因子 J (H 到 wi)
    // J = (eta_t^2 * abs(H . wi)) / (eta_i * abs(H . wo) + eta_t * abs(H . wi))^2
    float J_H_to_Wi_denominator_term = (current_etaI * std::abs(H_dot_Wo) + current_etaT * std::abs(H_dot_Wi));
    if (J_H_to_Wi_denominator_term == 0.0f) {
        pdf = 0.0f;
        return Color(0.0f);
    }
    float J_H_to_Wi = (current_etaT * current_etaT * std::abs(H_dot_Wi)) / (J_H_to_Wi_denominator_term * J_H_to_Wi_denominator_term);
    
    // 计算最终的 PDF
    // PDF = D(H) * |N . H| * J_H_to_Wi
    pdf = D_val * std::abs(local_N * H) * J_H_to_Wi; // J_H_to_Wi 已经为正

    // 确保 PDF 非负且有效
    if (pdf < MathConstant::FLOAT_SMALL_NUMBER) {
        pdf = 0.0f;
        return Color(0.0f);
    }

    // --- 4. 计算 BTDF 值本身 ---
    float G_val = ggx_G(local_wo, wi, local_N, alpha_); // 几何项
    
    Color T_color = Color(1.0f) - F_val_at_H; // 透射率 T = 1 - F

    // BTDF 公式分母中的项
    // denominator_term = (eta_i * abs(wo . H) + eta_t * abs(wi . H))
    float final_denominator_term = (current_etaI * std::abs(H_dot_Wo) + current_etaT * std::abs(H_dot_Wi));
    if (final_denominator_term == 0.0f) {
        return Color(0.0f);
    }
    // final_denominator_val = abs(N . wo) * abs(N . wi) * (denominator_term)^2
    float final_denominator_val = std::abs(cosThetaO) * std::abs(cosThetaI) * (final_denominator_term * final_denominator_term);

    if (final_denominator_val == 0.0f) {
        return Color(0.0f);
    }

    // BTDF 公式：f_t = [T * D * G * eta_t^2 * abs(wi . H)] / [abs(N . wo) * abs(N . wi) * (eta_i * abs(wo . H) + eta_t * abs(wi . H))^2]
    Color sampled_f = (T_color * D_val * G_val * (current_etaT * current_etaT) * std::abs(H_dot_Wi)) / final_denominator_val;

    sampled_f.clamp();
    sampled_f = Color::COLOR_WHITE;
    
    return sampled_f;
}

// f：评估给定入射和出射方向的 BTDF 值
// wo: 出射方向 (通常是相机方向)
// wi: 入射方向 (光线方向)
Color MicrofacetTransmissionBxdf::f(const Vector3 &wo, const Vector3 &wi) const
{
    // BxDF 在局部空间工作，表面法线 N 默认为 (0,0,1)
    // 根据重要提示，假定 wo 和 wi 已经在正确的半球，不需要翻转
    Vector3 N(0.0f, 0.0f, 1.0f); // 局部空间宏观法线
    if(!N.isSameDir(wo))
    {
        N = -N;
    }
    Vector3 local_wo = wo;       // 假设 wo 已经根据 N 调整到局部空间正确半球
    Vector3 local_N = N;         // 宏观法线保持 (0,0,1)
    Vector3 current_wi = wi;     // 假设 wi 已经根据 N 调整到局部空间正确半球

    float cosThetaO = local_wo * local_N;
    float cosThetaI = current_wi * local_N;

    // 1. 检查是否是透射方向 (wi 和 wo 必须在法线的不同半球)
    if (cosThetaO * cosThetaI >= 0) return Color(0.0f); // 同半球，不是透射
    if (cosThetaO == 0 || cosThetaI == 0) return Color(0.0f); // 掠射角，无贡献

    // 2. 调整折射率 (根据重要提示，这里不需要交换)
    float etaI_val = etaI_;
    float etaT_val = etaT_;
    
    // 3. 计算微面元半向量 H
    // H = normalize(eta_t * wo_local + eta_i * wi)
    Vector3 H = (local_wo * etaT_val + current_wi * etaI_val).dir();
    
    // 确保 H 指向和 local_N 相同的半球 (因为 NDF 定义在这个半球上)
    // 这一步非常重要，因为 D(H) 函数要求 H.z > 0
    if ((H * local_N) < 0)  
    {
        H = -H; // 翻转 H 使其指向 local_N 同侧
    }

    // 4. 检查是否发生全内反射 (TIR)
    float H_dot_Wo = H * local_wo;
    float H_dot_Wi = H * current_wi;
    float F_color_at_H = Common::fresnel(etaI_val, etaT_val, std::abs(H_dot_Wo), std::abs(H_dot_Wi)); 
    if (F_color_at_H == 1.0f) { // 如果菲涅尔反射率为1，表示全反射
        return Color(0.0f);
    }

    // 5. 计算 NDF (D) 
    float D_val = D(H); 
    
    // 6. 计算几何项 (G) 
    float G_val = ggx_G(local_wo, current_wi, local_N, alpha_); 

    // 7. 计算菲涅尔透射项 (1 - F) 
    Color T_color = Color(1.0f) - F_color_at_H; // (1 - F)

    // 8. 组装最终的 BTDF 值
    // denominator_term = (eta_i * abs(wo . H) + eta_t * abs(wi . H))
    float denominator_term = (etaI_val * std::abs(H_dot_Wo) + etaT_val * std::abs(H_dot_Wi)); 
    if (denominator_term == 0.0f) { 
        return Color(0.0f); 
    } 
    // denominator_val = abs(N . wo) * abs(N . wi) * (denominator_term)^2
    float denominator_val = std::abs(cosThetaO) * std::abs(cosThetaI) * (denominator_term * denominator_term);

    if (denominator_val == 0.0f) { 
        return Color(0.0f); 
    } 

    Color bt_f = (T_color * D_val * G_val * (etaT_val * etaT_val) * std::abs(H_dot_Wi)) / denominator_val; 
    
    return bt_f; 
}

// Pdf：评估给定入射和出射方向的 PDF 值
// wo: 出射方向
// wi: 入射方向
float MicrofacetTransmissionBxdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    // BxDF 在局部空间工作，表面法线 N 默认为 (0,0,1)
    // 根据重要提示，假定 wo 和 wi 已经在正确的半球，不需要翻转
    Vector3 N(0.0f, 0.0f, 1.0f); // 局部空间宏观法线
    if(!N.isSameDir(wo))
    {
        N = -N;
    }
    Vector3 local_wo = wo;       // 假设 wo 已经根据 N 调整到局部空间正确半球
    Vector3 local_N = N;         // 宏观法线保持 (0,0,1)
    Vector3 current_wi = wi;     // 假设 wi 已经根据 N 调整到局部空间正确半球

    float cosThetaO = local_wo * local_N;
    float cosThetaI = current_wi * local_N;

    // 1. 检查是否是透射方向 (wi 和 wo 必须在法线的不同半球)
    if (cosThetaO * cosThetaI >= 0) { // 同半球，不是透射
        return 0.0f;
    }
    if (cosThetaO == 0.0f || cosThetaI == 0.0f) { // 掠射角，PDF 为 0
        return 0.0f;
    }

    // 2. 调整折射率 (根据重要提示，这里不需要交换)
    float etaI_val = etaI_;
    float etaT_val = etaT_;  
    
    // 3. 反推微面元半向量 H
    Vector3 H = (local_wo * etaT_val + current_wi * etaI_val).dir();
    
    // 确保 H 指向和 local_N 相同的半球（因为 NDF 定义在这个半球上）
    // 这一步非常重要，因为 D(H) 函数要求 H.z > 0
    if ((H * local_N) < 0) {
        H = -H; // 翻转 H 使其指向 local_N 同侧
    }

    // 4. 检查是否发生全内反射 (TIR)
    float H_dot_Wo = H * local_wo;
    float H_dot_Wi = H * current_wi;
    float F_color_at_H = Common::fresnel(etaI_val, etaT_val, std::abs(H_dot_Wo), std::abs(H_dot_Wi)); 
    if (F_color_at_H == 1.0f) { // 如果菲涅尔反射率为1，表示全反射
        return 0.0f;
    }

    // 5. 计算 NDF (D) 
    float D_val = D(H); 

    // 6. 计算雅可比变换因子 J_H_to_Wi
    // sqrt_denom_term = (eta_i * abs(wo . H) + eta_t * abs(wi . H))
    float sqrt_denom_term = (etaI_val * std::abs(H_dot_Wo) + etaT_val * std::abs(H_dot_Wi)); 
    if (sqrt_denom_term == 0.0f) { 
        return 0.0f; 
    } 
    // J = (eta_t^2 * abs(H . wi)) / (eta_i * abs(H . wo) + eta_t * abs(H . wi))^2 
    float J_H_to_Wi = (etaT_val * etaT_val * std::abs(H_dot_Wi)) / (sqrt_denom_term * sqrt_denom_term); 
    
    // 7. 计算最终的 PDF 值
    // PDF = D(H) * |N . H| * J_H_to_Wi 
    float pdf_val = D_val * std::abs(local_N * H) * J_H_to_Wi; 
    
    return pdf_val; 
}

float MicrofacetTransmissionBxdf::D(const Vector3 &wh) const 
{ 
    if(wh.z <= 0) // 如果微面元法线指向宏观表面下方，则 NDF 为 0
        return 0.0f; 

    float alpha2 = alpha_ * alpha_; 
    float z2 = wh.z * wh.z; 

    float denominator_term = z2 * (alpha2 - 1.0f) + 1.0f; 
    float denominator = MathConstant::PI * denominator_term * denominator_term; 

    if (denominator == 0.0f) { 
        return 0.0f; 
    } 

    return alpha2 / denominator; 
} 

float MicrofacetTransmissionBxdf::ggx_G1(const Vector3& w, const Vector3& n, float alpha) const 
{ 
    float z = n * w; 

    if (z <= 0.0f) { // 几何遮蔽项 G1 对于指向表面下方的光线为 0
        return 0.0f; 
    } 

    float alpha2 = alpha * alpha; 
    float z2 = z * z; 

    float sqrt_term = std::sqrt(alpha2 + (1.0f - alpha2) * z2); 

    return (2.0f * z) / (z + sqrt_term); 
} 

float MicrofacetTransmissionBxdf::ggx_G(const Vector3& wi, const Vector3& wo, const Vector3& n, float alpha) const 
{ 
    return ggx_G1(wi, n, alpha) * ggx_G1(wo, n, alpha); 
}