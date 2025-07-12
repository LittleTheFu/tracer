#ifndef MICROFACET_TRANSMISSION_BXDF_H_
#define MICROFACET_TRANSMISSION_BXDF_H_

#include "bxdf.h"
#include "ray.h"
#include "interaction.h"
#include "material.h"
#include "geometry.h" // 确保包含所有需要的头文件
#include "mathConstantDef.h"
#include <common.h>   // 假设 Common::fresnel 定义在这里
#include <mathUtility.h> // 假设 MathUtility::genRandomDecimal 定义在这里

class MicrofacetTransmissionBxdf : public Bxdf
{
public:
    MicrofacetTransmissionBxdf(float roughness, float etaI, float etaT);
    ~MicrofacetTransmissionBxdf() = default;

    // SampleGGX: 根据 GGX 分布采样一个微面元法线 H
    // N: 宏观表面法线 (通常是局部空间的 (0,0,1))
    // roughness: 表面的粗糙度参数
    Vector3 SampleGGX(const Vector3& N, float roughness) const;

    // sample_f：根据 BTDF 采样一个入射方向，并返回该方向的 BTDF 值和 PDF
    // wo: 出射方向（通常是相机或当前光线方向）
    // wi: 输出参数，采样的入射方向（新的光线方向）
    // pdf: 输出参数，采样的概率密度函数值
    // interaction: 交互点信息
    Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const override;

    // f：评估给定入射和出射方向的 BTDF 值
    // wo: 出射方向 (通常是相机方向)
    // wi: 入射方向 (光线方向)
    Color f(const Vector3 &wo, const Vector3 &wi) const override;

    // Pdf：评估给定入射和出射方向的 PDF 值
    // wo: 出射方向
    // wi: 入射方向
    float pdf(const Vector3 &wo, const Vector3 &wi) const override;

private:
    float roughness_;
    float alpha_; // GGX 分布参数，通常是 roughness 的平方或直接使用 roughness
    float etaI_;  // 入射介质折射率
    float etaT_;  // 透射介质折射率

    // NDF 函数 (Normal Distribution Function)
    float D(const Vector3 &wh) const;

    // 几何遮蔽函数 G1
    float ggx_G1(const Vector3 &w, const Vector3 &H, float alpha) const;

    // 联合遮蔽函数 G (Smith G)
    float ggx_G(const Vector3& wi, const Vector3& wo, const Vector3& H, float alpha) const;
};

#endif // MICROFACET_TRANSMISSION_BXDF_H_
