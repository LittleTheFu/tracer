#include <algorithm>
#include <cassert>

#include "mathUtility.h"
#include "color.h"
#include "refreactorBsdf.h"

RefrectorBsdf::RefrectorBsdf(float etaOutsie, float etaInside)
{
    assert(etaInside != 0);
    assert(etaOutsie != 0);

    m_etaInside = etaInside;
    m_etaOutside = etaOutsie;
}

Color RefrectorBsdf::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    return Color::COLOR_BLACK;
}

Color RefrectorBsdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const
{
    // LOCAL_NORMAL 应该就是 TBN 空间中的 (0, 0, 1)
    Vector3 local_surface_normal = LOCAL_NORMAL; // (0,0,1)

    // wo 是出射方向，inputVector 是入射光线方向（用于 refract 函数）
    Vector3 inputVector = -wo; 

    // 这些 etaInputSide (etaI_) 和 etaOutputSide (etaT_)
    // 应该始终是材质的固定折射率，例如 1.0f (外部) 和 1.5f (内部)。
    // 不要在这里根据光线方向交换它们，让 refract 内部处理。
    float fixed_eta_outside = m_etaOutside; // 例如 1.0f (空气)
    float fixed_eta_inside = m_etaInside;   // 例如 1.5f (玻璃)

    bool totalReflect;
    float fresnel; // 存储菲涅尔反射率，但我们强制透射时不使用它来采样

    // 调用 refract 函数。refract 内部会根据 inputVector 和 local_surface_normal
    // 正确地调整其内部的 eta 和法线方向。
    wi = inputVector.refract(local_surface_normal, fixed_eta_outside, fixed_eta_inside, totalReflect, fresnel);

    // --- 强制只走透射逻辑 ---
    // 如果实际发生了全内反射，wi 已经被 refract 设置为反射方向。
    // 但是你这里强制透射，所以需要处理这种情况：
    if (totalReflect) {
        pdf = 0.0f;
        return Color::COLOR_BLACK; 
    }

    pdf = 1.0f; 

    // 计算透射颜色项。这需要基于光线实际穿过的介质进行校正。
    // inputVector 是入射方向 (TBN 空间)。
    // inputVector * local_surface_normal 是入射光线与局部法线的点积。
    float cos_theta_incident = inputVector * local_surface_normal;

    float actual_eta_incident; // 光线实际进入时的介质折射率
    float actual_eta_transmitted; // 光线实际透射到的介质折射率

    // 判断光线是从外部进入物体，还是从物体内部射出到外部
    if (cos_theta_incident < 0) { // 光线从 LOCAL_NORMAL 的负方向进入（例如从空气到玻璃）
        actual_eta_incident = fixed_eta_outside; // 空气
        actual_eta_transmitted = fixed_eta_inside; // 玻璃
    } else { // 光线从 LOCAL_NORMAL 的正方向射出（例如从玻璃到空气）
        actual_eta_incident = fixed_eta_inside; // 玻璃
        actual_eta_transmitted = fixed_eta_outside; // 空气
    }

    // 透射的颜色校正项是 (eta_incident / eta_transmitted)^2
    // 这个因子是为了在传输光线时保持能量守恒 (Li/PDF * BTDF)
    Color final_transmittance_color = Color::COLOR_WHITE;
    
    // 🔴 关键修正：无论光线方向如何，都应用这个折射率比的平方因子
    final_transmittance_color = final_transmittance_color * MathUtility::sq(actual_eta_incident / actual_eta_transmitted);
    
    return final_transmittance_color;
}

float RefrectorBsdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    return 0.0f;
}

std::shared_ptr<Brdf> RefrectorBsdf::clone() const
{
    return std::make_shared<RefrectorBsdf>(*this);
}
