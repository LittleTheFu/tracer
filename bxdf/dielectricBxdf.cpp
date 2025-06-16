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

// dielectricBxdf.cpp

Color DielectricBxdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const
{
    // 1. 局部空间法线 (wo 已在 BTN 空间，法线是 Z 轴)
    Vector3 local_surface_normal = Vector3(0, 0, 1); 
    
    // interaction.incoming 是世界空间的入射光线方向，与 wo (-inputVector) 不同。
    // 在这里，我们已经知道 wo 是局部空间的，且 local_surface_normal 是局部空间的 (0,0,1)。
    // 因此，不再需要根据 wo.z 来调整 etaI/etaT。
    // DielectricBxdf 构造函数接收的 etaI_ 和 etaT_ 已经是正确的“入射介质”和“透射介质”折射率。
    
    // 直接使用成员变量 etaI_ 和 etaT_
    float eta_incident = etaI_; 
    float eta_transmitted = etaT_; 

    Vector3 inputVector = -wo; // 入射光线方向 (局部空间)

    bool totalReflect;
    float fresnel;
    // 调用 refract 函数：
    // - normal 参数始终是局部空间的 (0,0,1)
    // - etaI/etaT 参数是构造函数中已经根据光线进入/离开方向调整好的
    Vector3 temp_refracted_wi_local = inputVector.refract(local_surface_normal, 
                                                           eta_incident, 
                                                           eta_transmitted, 
                                                           totalReflect, 
                                                           fresnel);

    // 调试断言：菲涅尔系数应在 [0, 1] 范围内 (容忍度使用 MathConstant::FLOAT_SMALL_NUMBER)
    // 1 + 0.00001f 最好写成 1.0f + MathConstant::FLOAT_SMALL_NUMBER (如果定义了)
    assert(MathUtility::is_in_range(fresnel, 0.0f, 1.0f + 1e-5f, true, true)); 

    // 为避免除以非常小的数，设置最小概率阈值
    const float MIN_PROBABILITY_THRESHOLD = 1e-6f; 

    // 2. 处理全内反射 (TIR) 或基于菲涅尔概率的反射/折射
    if (totalReflect) {
        // 如果发生全内反射，则光线只能反射。
        wi = inputVector.reflect(local_surface_normal); // 计算反射方向 (局部空间)
        
        // 全内反射时，菲涅尔系数 fresnel 理论上为 1.0。
        // 采样概率为 1.0。
        pdf = 1.0f; 

        // BxDF 值为 Color::WHITE * fresnel / pdf = Color::WHITE * 1.0 / 1.0 = Color::WHITE
        // 你的原始代码这里是 `Color::COLOR_WHITE * fresnel;`。
        // 如果 fresnel 确保是 1.0，直接返回 Color::COLOR_WHITE 即可。
        // 如果为了通用性（即使 Fresnel 略小于1也保持乘法），则保留 `* fresnel` 也行，但 PDF 是 1。
        // 考虑到这里是 TIR，fresnel 应该是 1。
        return Color::COLOR_WHITE; // 修正点：通常直接返回 Color::WHITE
    }
    else {
        // 非 TIR 情况：根据菲涅尔系数进行概率采样 (俄罗斯轮盘赌)
        float rand_val = MathUtility::genRandomDecimal();

        if (rand_val < fresnel) {
            // 采样反射路径 (概率为 fresnel)
            wi = inputVector.reflect(local_surface_normal); // 计算反射方向 (局部空间)
            
            // PDF 是选择反射路径的概率，钳制以防过小
            pdf = std::max(MIN_PROBABILITY_THRESHOLD, fresnel); 
            
            // BxDF 值 = (Color::WHITE * fresnel) / pdf
            return Color::COLOR_WHITE * (fresnel / pdf); 
        } else {
            // 采样折射路径 (概率为 1 - fresnel)
            // 修正点：wi 应该赋值为折射方向 temp_refracted_wi_local
            wi = temp_refracted_wi_local; 
            
            // PDF 是选择折射路径的概率，钳制以防过小
            float transmittance_prob = 1.0f - fresnel;
            pdf = std::max(MIN_PROBABILITY_THRESHOLD, transmittance_prob); 
            
            // 镜面透射的 BxDF 值为 Color::WHITE * (1 - fresnel) * (etaI / etaT)^2
            // 修正点：这里的 etaI / etaT 应该使用成员变量 etaI_ / etaT_
            // 因为它们已经代表了正确的入射/透射折射率
            return Color::COLOR_WHITE * (transmittance_prob / pdf) * MathUtility::sq(etaI_ / etaT_); 
        }
    }
}