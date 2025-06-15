#include "dielectricBxdf.h"
#include <mathUtility.h>
#include <cassert>

DielectricBxdf::DielectricBxdf(float etaI, float etaT)
    : Bxdf(static_cast<BxdfType>(BxdfType::SPECULAR | BxdfType::REFLECTION | BxdfType::TRANSMISSION))
{
    etaI_ = etaI;
    etaT_ = etaT;
}

Color DielectricBxdf::f(const Vector3 &wo, const Vector3 &wi) const
{
    return Color::COLOR_BLACK;
}

float DielectricBxdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    return 0.0f;
}

Color DielectricBxdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const
{
    Vector3 normal = Vector3(0, 0, 1);
    float dot = wo * normal;

    float etaI = etaI_;
    float etaT = etaT_;

    if (dot > 0)
    {
        normal = -normal;
    }

    Vector3 inputVector = -wo;
    bool totalReflect;
    float fresnel;
    Vector3 temp_refracted_wi = inputVector.refract(normal, etaI, etaT, totalReflect, fresnel);

    assert(MathUtility::is_in_range(fresnel, 0.0f, 1 + 0.00001f, true, true));


   // 2.1. 内全反射 (TIR)
    if (totalReflect) {
        // 如果发生全内反射，则光线只能反射。
        wi = inputVector.reflect(normal); // 确保 wi 是正确的反射方向
        pdf = 1.0f; // 确定性采样，PDF为1.0。
        // Fresnel 在 TIR 时应该为 1.0。BxDF 值为 Color::WHITE * fresnel (即 Color::WHITE)。
        return Color::COLOR_WHITE * fresnel; 
    } 
    // 2.2. 非 TIR 情况：概率反射或概率折射
    else {
        // 生成一个随机数来决定是反射还是折射
        float rand_val = MathUtility::genRandomDecimal();

        if (rand_val < fresnel) {
            // 采样反射路径 (概率为 fresnel)
            wi = inputVector.reflect(normal); // 计算反射方向
            pdf = fresnel; // 采样反射路径的 PDF
            // 镜面反射的 BxDF 值为 Color::WHITE * fresnel。
            // 返回 f / pdf = (Color::WHITE * fresnel) / fresnel = Color::WHITE。
            return Color::COLOR_WHITE; 
        } else {
            // 采样折射路径 (概率为 1 - fresnel)
            wi = temp_refracted_wi; // wi 是之前 refract 计算得到的折射方向
            pdf = 1.0f - fresnel; // 采样折射路径的 PDF
            // 镜面透射的 BxDF 值为 Color::WHITE * (1 - fresnel) * (etaI / etaT)^2。
            // 返回 f / pdf = (Color::WHITE * (1.0f - fresnel) * MathUtility::sq(etaI / etaT)) / (1.0f - fresnel)
            //               = Color::COLOR_WHITE * MathUtility::sq(etaI / etaT)。
            return Color::COLOR_WHITE * MathUtility::sq(etaI / etaT);
        }
    }
}
