#include "microfacetSpecularBxdf.h"
#include "mathConstantDef.h"
#include "common.h"
#include "mathUtility.h"

MicrofacetSpecularBxdf::MicrofacetSpecularBxdf(float roughness)
    : Bxdf(BxdfType::REFLECTION | BxdfType::GLOSSY)
{
    // roughness = 0.15;
    roughness_ = roughness;
    alpha_ = roughness;

    if (alpha_ <= 0)
        alpha_ = MathConstant::FLOAT_SMALL_NUMBER;
}

Color MicrofacetSpecularBxdf::f(const Vector3 &wo, const Vector3 &wi) const
{
    if(wo.z <= 0 || wi.z <= 0)
        return Color::COLOR_BLACK;

    Vector3 wh = (wo + wi).dir();

    //----------------------------------------------------
    Color eta(0.2, 0.92, 1.1);
    Color k(3.9, 2.45, 2.14);
    float dot = std::abs(wo * wh);
    Color F = Common::FresnelConductor(dot, eta, k);
    //----------------------------------------------------

    // bool totalReflect = false;
    // float f;
    // Vector3 wt = wi.refract(wh, etaI_, etaT_, totalReflect, f);
 
    // f = 1;
    // std::cout << "f:" << f << std::endl;
    float d = D(wh);
    float g = ggx_G(wi, wo, Vector3(0,0,1), alpha_);

    return Color(d * g * F / (4.0f * wo.z * wi.z));
    // return Color(d * g * f / (4.0f * wo.z * wi.z));
}

float MicrofacetSpecularBxdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    if(wo.z <= 0 || wi.z <= 0)
        return 0.0f;

    Vector3 wh = (wo + wi).dir();
    
    if(wh.isZero() || wh.z <= 0)
        return 0.0f;

    float d_val = D(wh);
    float NdotH = std::abs(wh.z);
    float HdotI = std::abs(wh * wi);

    const float EPSILON = MathConstant::FLOAT_SMALL_NUMBER;
    float denominator = 4.0f * HdotI;

    if (denominator < EPSILON) {
        return 0.0f;
    }

    float pdf_val = (d_val * NdotH) / denominator;

    return pdf_val;
}

Color MicrofacetSpecularBxdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const
{
    float u1 = MathUtility::genRandomDecimal();
    float u2 = MathUtility::genRandomDecimal();

    // 2. 根据 GGX NDF 采样微面元法线 wh (在局部坐标系中)
    // 计算 cos_theta_h (wh.z)
    // Clamp u2 to avoid division by zero or sqrt of negative
    u2 = std::max(MathConstant::FLOAT_SMALL_NUMBER, u2); // avoid u2 = 0
    u2 = std::min(1.0f - MathConstant::FLOAT_SMALL_NUMBER, u2); // avoid u2 = 1

    float cos_theta_h = std::sqrt((1.0f - u2) / (alpha_ * alpha_ * u2 + 1.0f - u2));
    float sin_theta_h = std::sqrt(std::max(0.0f, 1.0f - cos_theta_h * cos_theta_h)); // 确保非负

    // 计算 phi_h
    float phi_h = 2.0f * MathConstant::PI * u1;

    // 将极坐标转换为直角坐标得到 wh
    Vector3 wh;
    wh.x = sin_theta_h * std::cos(phi_h);
    wh.y = sin_theta_h * std::sin(phi_h);
    wh.z = cos_theta_h;

    // 确保 wh.z 指向上方，如果不是，则采样无效
    // 理论上由于 cos_theta_h 的计算方式，wh.z 应该总是 >= 0，但为了健壮性可以检查
    if (wh.z <= 0.0f) {
        pdf = 0.0f;
        return Color::COLOR_BLACK;
    }

    // 3. 将 wh 转换到 wi (入射方向)
    // 反射定律：wi = 2 * dot(wo, wh) * wh - wo
    float WodotH = wo * wh; // 使用你的 Vector3::operator* 进行点积

    // 检查 WodotH 是否有效，如果为负，则表示 wo 和 wh 方向相反，反射方向会指向表面下方
    if (WodotH <= 0.0f) { // wo 和 wh 的点积必须是正的，否则反射光线会指向表面下方
        pdf = 0.0f;
        return Color::COLOR_BLACK;
    }

    wi = 2.0f * WodotH * wh - wo;

    // 4. 检查生成的 wi 是否有效 (必须在宏观表面上方)
    if (wi.z <= 0.0f) {
        pdf = 0.0f;
        return Color::COLOR_BLACK;
    }

    // 5. 计算 pdf 值
    pdf = MicrofacetSpecularBxdf::pdf(wo, wi); // 调用你刚刚实现的 pdf 函数

    // 如果 pdf 为 0，也返回黑色
    if (pdf <= MathConstant::FLOAT_SMALL_NUMBER) { // 使用 epsilon 比较
        return Color::COLOR_BLACK;
    }

    // 6. 计算并返回 BRDF 值
    return f(wo, wi); // 调用 MicrofacetSpecularBxdf::f 函数
}

float MicrofacetSpecularBxdf::D(const Vector3 &wh) const
{
    if(wh.z < 0)
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

float MicrofacetSpecularBxdf::ggx_G1(const Vector3& w, const Vector3& n, float alpha) const
{
    float z = n * w;

    if (z <= 0.0f) {
        return 0.0f;
    }

    float alpha2 = alpha * alpha;
    float z2 = z * z;

    float sqrt_term = std::sqrt(alpha2 + (1.0f - alpha2) * z2);

    return (2.0f * z) / (z + sqrt_term);
}

float MicrofacetSpecularBxdf::ggx_G(const Vector3& wi, const Vector3& wo, const Vector3& n, float alpha) const
{
    return ggx_G1(wi, n, alpha) * ggx_G1(wo, n, alpha);
}
