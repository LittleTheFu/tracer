// #include "microfacetTransmissionBxdf.h"
// #include "mathConstantDef.h"
// #include <common.h>
// #include <mathUtility.h>

// MicrofacetTransmissionBxdf::MicrofacetTransmissionBxdf(float roughness)
//     : Bxdf(BxdfType::TRANSMISSION | BxdfType::GLOSSY)
// {
//     // roughness = 0.15;
//     roughness_ = roughness;
//     alpha_ = roughness;

//     if (alpha_ <= 0)
//         alpha_ = MathConstant::FLOAT_SMALL_NUMBER;
// }

// // SampleGGX: 根据 GGX 分布采样一个微面元法线 H
// // N: 宏观表面法线 (通常是局部空间的 (0,0,1))
// // sample: 均匀分布的二维随机样本 (u1, u2)
// // roughness: 表面的粗糙度参数
// Vector3 MicrofacetTransmissionBxdf::SampleGGX(const Vector3& N, float roughness) const
// {
//     // 将 roughness 转换为 alpha (通常 alpha = roughness * roughness，或直接使用 roughness)
//     // 根据你的 D 函数 (float MicrofacetTransmissionBxdf::D(const Vector3 &wh) const)
//     // 你的 D 函数内部使用 alpha_ 成员变量，而 alpha_ = roughness 在你的构造函数中
//     // 所以这里的 alpha 直接使用传入的 roughness (即 alpha_)
//     float alpha = roughness; // 对应你的 alpha_

//     // 1. 生成球面坐标
//     // phi 是方位角，theta 是极角
//     float u1 = MathUtility::genRandomDecimal();
//     float u2 = MathUtility::genRandomDecimal();

//     float phi = MathConstant::TWO_PI * u1; // 0 到 2PI
    
//     // 计算 cosThetaH
//     // 这里的公式是从 PBRT v3 中 GGX 采样的倒数转换而来
//     float cosThetaH = std::sqrt((1.0f - u2) / (1.0f + (alpha * alpha - 1.0f) * u2));
//     float sinThetaH = std::sqrt(std::max(0.0f, 1.0f - cosThetaH * cosThetaH)); // 确保不为负

//     // 2. 将球面坐标转换为标准正交基下的 H (N=(0,0,1))
//     Vector3 H_local;
//     H_local.x = sinThetaH * std::cos(phi);
//     H_local.y = sinThetaH * std::sin(phi);
//     H_local.z = cosThetaH;

//     // 如果你的 N 不是 (0,0,1)，你需要一个切线空间到世界空间的转换矩阵。
//     // 但在 BxDF 的局部空间，N 总是 (0,0,1)，所以 H_local 就是我们需要的 H。
//     // 确保 H_local 的 Z 分量（即 H_local * N，因为 N=(0,0,1)）是非负的
//     // 由于 cosThetaH 是非负的，H_local.z 必然是非负的，所以无需额外翻转。

//     return H_local;
// }

// // sample_f：根据 BTDF 采样一个入射方向，并返回该方向的 BTDF 值和 PDF
// // wo: 出射方向（通常是相机或当前光线方向）
// // wi: 输出参数，采样的入射方向（新的光线方向）
// // pdf: 输出参数，采样的概率密度函数值
// // sample: 均匀分布的随机数，用于蒙特卡洛采样
// Color MicrofacetTransmissionBxdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const
// {
//     // BxDF 在局部空间工作，表面法线 N 默认为 (0,0,1)
//     // 根据你的 Interaction 结构体，这里可能需要从 interaction 中获取法线并转换到局部空间
//     // 但是通常 BxDF 内部处理的是局部空间，所以通常假定 N 是 (0,0,1)
//     // 实际的法线转换应该在 BSDF 层进行。
//     Vector3 N(0.0f, 0.0f, 1.0f); // 局部空间宏观法线

//     float cosThetaO = wo * N; // wo 和 N 的点积
//     if (cosThetaO == 0.0f) {
//         pdf = 0.0f;
//         return Color(0.0f);
//     }
    
//     // 如果 wo 指向背面，则翻转 wo 和 N，使 wo 始终在法线正面
//     // 这样做是为了简化 NDF、几何项和菲涅尔项的计算，它们通常假定所有向量都在法线的正半球
//     Vector3 local_wo = wo;
//     Vector3 local_N = N;
//     if (cosThetaO < 0) {
//         local_wo = -wo;
//         local_N = -N;
//     }

//     // --- 1. 采样微面元法线 H ---
//     // 你需要提供 SampleGGX 的实现。它应该根据 roughness 参数和随机样本生成一个 H。
//     // H 应该在 local_N 所在的半球。
//     // SampleGGX 函数原型可能如下：Vector3 SampleGGX(const Vector3& N, const Vector2& sample, float roughness);
//     Vector3 H = SampleGGX(local_N, alpha_); // 使用 roughness_ 成员变量

//     // --- 2. 根据 H 和 local_wo 计算折射方向 wi ---
//     // MathUtility::refractMicrofacet 需要入射方向、微面元法线、入射折射率、出射折射率和输出的折射方向。
//     // 在这里，local_wo 是“出射”方向（例如，相机方向），但对于微面元折射，我们需要它作为光线“入射”到微面元的方向。
//     // 因此，我们将 -local_wo 作为 MathUtility::refractMicrofacet 的“入射”方向。
    
//     float current_etaI = etaI_; // 介质1的折射率
//     float current_etaT = etaT_; // 介质2的折射率

//     // 如果 local_wo 是从内部指向外部，那么当前折射率需要反转。
//     // 例如，如果光线是从物体内部射出，那么物体内部是 etaI，外部是 etaT。
//     // 这里我们统一约定，光线总是从 current_etaI 射向 current_etaT。
//     // local_wo (相机方向) 总是和 local_N (宏观法线) 在同一侧。
//     // 如果 local_wo 所在的半球是物体内部，那么 light_incident_to_microfacet 是从物体内部射向外部。
//     // 这里的逻辑有点微妙，取决于你的渲染器如何处理内外折射率。
//     // PBRT 约定：`refract(wi_incident_ray_from_outside, normal, etaI, etaT, &wi_refracted_ray_inside)`
//     // 在我们的场景中，`local_wo` 是相机方向，我们要找到 `wi` (入射光线)。
//     // 所以，我们用 `-local_wo` 作为微面元的“入射”方向，如果 `local_N` 指向外部。
//     // 
//     // 正确的折射率交换逻辑通常在 `refractMicrofacet` 内部处理，
//     // 或者根据 `interaction` 的 `outside()` 状态来确定。
//     // 假设 `refractMicrofacet` 已经处理了折射率的自动交换
//     // 或者根据你的设定，`etaI_` 总是当前介质，`etaT_` 是目标介质。
//     // 让我们假设我们根据 `local_N` 的方向来确定内外介质。
//     // 如果 `local_N` 指向外部 (默认情况)，并且 `local_wo` 是外部光线 (相机)，
//     // 那么入射到微面元的光线 `-local_wo` 是从外部介质 `etaI_` 射入内部介质 `etaT_`。
//     // 所以保持 `etaI_` 和 `etaT_` 不变。

//     // MathUtility::refractMicrofacet 返回是否成功 (0.0f 表示全内反射)。
//     // 它通常需要入射光线指向法线。
//     // 我们的 local_wo 是出射方向，所以实际入射到微面元的光线方向是 -local_wo。
//     bool isTotalReflected = false;
//     float f;
//     wi = (-local_wo).refract(H, current_etaI, current_etaT, isTotalReflected, f);

//     // 如果发生全内反射 (TIR) 或者折射到同一半球（不应该发生，因为是透射），则透射失败
//     // wi 必须在宏观法线的另一侧
//     float cosThetaI = wi * N; // 计算采样到的 wi 与原始宏观法线 N 的点积
//     if (isTotalReflected || cosThetaI * cosThetaO >= 0.0f) {
//         pdf = 0.0f;
//         return Color(0.0f);
//     }
    
//     // --- 3. 计算 PDF for Transmission ---
//     // PDF 的计算公式通常为：Pdf(wi) = D(H) * |N . H| * J_H_to_Wi
//     // 其中 J_H_to_Wi 是从 H 采样到 wi 采样的雅可比变换因子。
    
//     float D_val = D(H); // NDF 值，使用你的 D 函数 (它使用 alpha_)

//     float H_dot_Wo = H * local_wo; // H . wo
//     float H_dot_Wi = H * wi;       // H . wi (这里 wi 已经是折射后的方向)

//     // 检查是否发生全内反射。
//     // PBRT 中的菲涅尔函数通常在内部处理了 `abs`，并且根据折射率来决定是否全反射。
//     // 如果 fresnel 函数返回 1.0f，则表示全反射。
//     // MathUtility::fresnel 的签名可能需要调整，这里假设它接受入射角余弦值和折射率
//     float F_val_at_H = Common::fresnel(current_etaI, current_etaT, std::abs(H_dot_Wo), std::abs(H_dot_Wi));
//     if (F_val_at_H == 1.0f) { // 如果菲涅尔反射率为1，表示全反射
//         pdf = 0.0f;
//         return Color(0.0f);
//     }

//     // 雅可比变换因子 J (H 到 wi)
//     // J = (eta_t^2 * abs(H . wi)) / (eta_i * abs(H . wo) + eta_t * abs(H . wi))^2
//     // 注意这里使用的 etaI_val 和 etaT_val 应该是 `refractMicrofacet` 实际使用的。
//     // 由于我们在 refractMicrofacet 之前没有对 etaI_ 和 etaT_ 进行交换，
//     // 那么这里也应该使用原始的 etaI_ 和 etaT_。
//     float J_H_to_Wi_denominator_term = (current_etaI * H_dot_Wo + current_etaT * H_dot_Wi);
//     // 避免除以零
//     if (J_H_to_Wi_denominator_term == 0.0f) {
//         pdf = 0.0f;
//         return Color(0.0f);
//     }
//     float J_H_to_Wi = (current_etaT * current_etaT * std::abs(H_dot_Wi)) / (J_H_to_Wi_denominator_term * J_H_to_Wi_denominator_term);
    
//     // 计算最终的 PDF
//     // PDF = D(H) * |N . H| * J_H_to_Wi
//     // 注意：这里的 abs(cos((local_N * H))) 等同于 std::abs(local_N * H)
//     pdf = D_val * std::abs(local_N * H) * std::abs(J_H_to_Wi);
//     // 确保 PDF 非负且有效
//     if (pdf < MathConstant::FLOAT_SMALL_NUMBER) { // 使用一个小的浮点数，避免 PDF 过小或为零
//         pdf = 0.0f;
//         return Color(0.0f);
//     }

//     // --- 4. 计算 BTDF 值本身 ---
//     // 这是 BTDF 公式 f_t(wo, wi)，与 f() 函数的计算相同
    
//     float G_val = ggx_G(local_wo, wi, local_N, roughness_); // 使用你的 ggx_G 函数，参数为 roughness_
    
//     // 透射率 T = 1 - F
//     Color T_color = Color(1.0f) - F_val_at_H;

//     // BTDF 公式：f_t = [T * D * G * eta_t^2 * abs(wi . H)] / [abs(N . wo) * abs(N . wi) * (eta_i * abs(wo . H) + eta_t * abs(wi . H))^2]
//     // 分母中的 cosThetaO 是 wo 与原始宏观法线 N 的点积
//     // cosThetaI 是 wi 与原始宏观法线 N 的点积
    
//     float final_denominator_term = (current_etaI * H_dot_Wo + current_etaT * H_dot_Wi);
//     if (final_denominator_term == 0.0f) {
//         return Color(0.0f);
//     }
//     float final_denominator_val = std::abs(cosThetaO) * std::abs(cosThetaI) * (final_denominator_term * final_denominator_term);

//     if (final_denominator_val == 0.0f) {
//         return Color(0.0f);
//     }

//     Color sampled_f = (T_color * D_val * G_val * (current_etaT * current_etaT) * std::abs(H_dot_Wi)) / final_denominator_val;
    
//     return sampled_f;
// }

// // f：评估给定入射和出射方向的 BTDF 值
// // wo: 出射方向 (通常是相机方向)
// // wi: 入射方向 (光线方向)
// Color MicrofacetTransmissionBxdf::f(const Vector3 &wo, const Vector3 &wi) const
// {
//     // BxDF 在局部空间工作，表面法线 N 默认为 (0,0,1)
//     Vector3 N(0.0f, 0.0f, 1.0f); // 局部空间宏观法线

//     float cosThetaO = wo * N;
//     float cosThetaI = wi * N;

//     // 1. 检查是否是透射方向 (wi 和 wo 必须在法线的不同半球)
//     if (cosThetaO * cosThetaI >= 0) return Color(0.0f); // 同半球，不是透射
//     if (cosThetaO == 0 || cosThetaI == 0) return Color(0.0f); // 掠射角，无贡献

//     // 2. 确保 wo 指向法线的正面 (为了统一处理)
//     Vector3 local_wo = wo;
//     Vector3 local_N = N;
//     if (cosThetaO < 0) {
//         local_wo = -wo;
//         local_N = -N;
//     }

//     // 3. 调整折射率以匹配光线方向
//     float etaI_val = etaI_;
//     float etaT_val = etaT_;
    
//     // 如果 wi 指向 local_N 的正面（即光线从高密度介质内部射出），则交换折射率
//     // 这样，wi 总是从 etaI_val 介质射入 etaT_val 介质
//     Vector3 current_wi = wi;
//     if (current_wi * local_N > 0) { // wi 在 local_N 的正方向，说明光线是从内部射出
//         std::swap(etaI_val, etaT_val);
//     }
    
//     // 4. 计算微面元半向量 H
//     // H = normalize(eta_t * wo_local + eta_i * wi)
//     Vector3 H = (local_wo * etaT_val + current_wi * etaI_val).dir();
    
//     // 确保 H 指向和 local_N 相同的半球 (因为 NDF 定义在半球上)
//     if (H * local_N < 0) H = -H;

//     // 5. 检查是否发生全内反射 (TIR)
//     // 如果发生全内反射，那么透射是不可能的，BTDF 为 0。
//     // 计算微面元层面的菲涅尔反射率。
//     float H_dot_Wo = (H * local_wo);
//     float H_dot_Wi = (H * current_wi);
//     float F_color_at_H = Common::fresnel(etaI_val, etaT_val, std::abs(cos(H_dot_Wo)), std::abs(cos(H_dot_Wi)));
//     if (F_color_at_H == 1.0f) { // 如果平均菲涅尔反射率为1，表示全反射
//         return Color(0.0f);
//     }

//     // 6. 计算 NDF (D)
//     float D_val = D(H); // 使用你提供的 D 函数 (它使用 alpha_)
    
//     // 7. 计算几何项 (G)
//     float G_val = ggx_G(local_wo, current_wi, local_N, alpha_); // 使用你提供的 ggx_G 函数
//                                                                     // 注意：ggx_G 内部会调用 ggx_G1(wi, n, alpha) 和 ggx_G1(wo, n, alpha)

//     // 8. 计算菲涅尔透射项 (1 - F)
//     Color T_color = Color(1.0f) - F_color_at_H; // (1 - F)

//     // 9. 计算 BTDF 公式中的其他点积项
//     // float H_dot_Wi = (H * current_wi); // H . wi
    
//     // 10. 组装最终的 BTDF 值
//     // 使用 PBRT 中的公式形式
//     // f_t = [D(H) * G(wo, wi, H) * (1 - F(wo, H)) * eta_t^2 * abs(wi . H)] / [abs(N . wo) * abs(N . wi) * (eta_i * abs(wo . H) + eta_t * abs(wi . H))^2]

//     float denominator_term = (etaI_val * H_dot_Wo + etaT_val * H_dot_Wi);
//     // 避免除以零
//     if (denominator_term == 0.0f) {
//         return Color(0.0f);
//     }
//     float denominator_val = std::abs(cos(cosThetaO)) * std::abs(cos(cosThetaI)) * (denominator_term * denominator_term);

//     if (denominator_val == 0.0f) {
//         return Color(0.0f);
//     }

//     Color bt_f = (T_color * D_val * G_val * (etaT_val * etaT_val) * std::abs(H_dot_Wi)) / denominator_val;
    
//     return bt_f;
// }
// // Pdf：评估给定入射和出射方向的 PDF 值
// // wo: 出射方向
// // wi: 入射方向
// float MicrofacetTransmissionBxdf::pdf(const Vector3 &wo, const Vector3 &wi) const
// {
//     // BxDF 在局部空间工作，表面法线 N 默认为 (0,0,1)
//     Vector3 N(0.0f, 0.0f, 1.0f); // 局部空间宏观法线

//     float cosThetaO = wo * N;
//     float cosThetaI = wi * N;

//     // 1. 检查是否是透射方向 (wi 和 wo 必须在法线的不同半球)
//     if (cosThetaO * cosThetaI >= 0) { // 同半球，不是透射
//         return 0.0f;
//     }
//     if (cosThetaO == 0.0f || cosThetaI == 0.0f) { // 掠射角，PDF 为 0
//         return 0.0f;
//     }

//     // 2. 确保 wo 指向法线的正面 (为了统一处理)
//     // local_N 指向和 wo 相同的半球
//     Vector3 local_wo = wo;
//     Vector3 local_N = N;
//     if (cosThetaO < 0) {
//         local_wo = -wo;
//         local_N = -N;
//     }

//     // 3. 调整折射率以匹配光线方向
//     // 确保 etaI_val 是入射介质的折射率，etaT_val 是透射介质的折射率
//     float etaI_val = etaI_;
//     float etaT_val = etaT_; 
    
//     // 如果 wi 指向 local_N 的正面（即光线从高密度介质内部射出），则交换折射率
//     // 这样，wi 总是从 etaI_val 介质射入 etaT_val 介质
//     Vector3 current_wi = wi; // 保持 wi 不变，但根据其方向调整折射率
//     if ((current_wi * local_N) > 0) { // wi 在 local_N 的正方向，说明光线是从内部射出
//         std::swap(etaI_val, etaT_val);
//     }

//     // 4. 反推微面元半向量 H
//     // H = normalize(eta_t * wo_local + eta_i * wi)
//     // 这是根据折射公式反推 H 的形式
//     Vector3 H = (local_wo * etaT_val + current_wi * etaI_val).dir();
    
//     // 确保 H 指向和 local_N 相同的半球（因为 NDF 定义在这个半球上）
//     if ((H * local_N) < 0) {
//         H = -H; // 翻转 H
//     }

//     // 5. 检查是否发生全内反射 (TIR)
//     // 如果发生全内反射，那么这条路径的透射是不可能的，PDF 应该为 0。
//     // 计算微面元层面的菲涅尔反射率。
//     float H_dot_Wo = H * local_wo;
//     float H_dot_Wi = H * current_wi;
//     float F_color_at_H = Common::fresnel(etaI_val, etaT_val, H_dot_Wo, std::abs(H_dot_Wi));
//     if (F_color_at_H == 1.0f) { // 如果平均菲涅尔反射率为1，表示全反射
//         return 0.0f;
//     }

//     // 6. 计算 NDF (D)
//     float D_val = D(H); // 使用你已经实现的 D 函数（它使用 alpha_ 成员变量）

//     // 7. 计算雅可比变换因子 J_H_to_Wi
//     // 这个雅可比因子与 sample_f 中用于将 H 采样的 PDF 转换为 wi 采样的 PDF 的因子相同
//     // float H_dot_Wi = H * current_wi; // H 与当前入射方向 wi 的点积
//     float sqrt_denom_term = (etaI_val * H_dot_Wo + etaT_val * H_dot_Wi);
//     // 雅可比公式：J = (eta_t^2 * abs(H . wi)) / (eta_i * abs(H . wo) + eta_t * abs(H . wi))^2
//     float J_H_to_Wi = (etaT_val * etaT_val * H_dot_Wi) / (sqrt_denom_term * sqrt_denom_term);
    
//     // 8. 计算最终的 PDF 值
//     // PDF = D(H) * |N . H| * J_H_to_Wi (这是基于采样的 PDF 转换关系)
//     float pdf_val = D_val * std::abs(cos((local_N * H))) * std::abs(J_H_to_Wi);
    
//     return pdf_val;
// }

// float MicrofacetTransmissionBxdf::D(const Vector3 &wh) const
// {
//     if(wh.z < 0)
//         return 0.0f;

//     float alpha2 = alpha_ * alpha_;
//     float z2 = wh.z * wh.z;

//     float denominator_term = z2 * (alpha2 - 1.0f) + 1.0f;
//     float denominator = MathConstant::PI * denominator_term * denominator_term;

//     if (denominator == 0.0f) {
//         return 0.0f;
//     }

//     return alpha2 / denominator;
// }

// float MicrofacetTransmissionBxdf::ggx_G1(const Vector3& w, const Vector3& n, float alpha) const
// {
//     float z = n * w;

//     if (z <= 0.0f) {
//         return 0.0f;
//     }

//     float alpha2 = alpha * alpha;
//     float z2 = z * z;

//     float sqrt_term = std::sqrt(alpha2 + (1.0f - alpha2) * z2);

//     return (2.0f * z) / (z + sqrt_term);
// }

// float MicrofacetTransmissionBxdf::ggx_G(const Vector3& wi, const Vector3& wo, const Vector3& n, float alpha) const
// {
//     return ggx_G1(wi, n, alpha) * ggx_G1(wo, n, alpha);
// }
