// #ifndef _MICROFACET_TRANSMISSION_BXDF_H_
// #define _MICROFACET_TRANSMISSION_BXDF_H_

// #include "bxdf.h"

// class MicrofacetTransmissionBxdf : public Bxdf
// {
// public:
//     MicrofacetTransmissionBxdf(float roughness);

//     virtual Color f(const Vector3 &wo, const Vector3 &wi) const override;
//     virtual float pdf(const Vector3 &wo, const Vector3 &wi) const override;

//     virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const override;

// private:
//     Vector3 SampleGGX(const Vector3& N, float roughness) const;
//     float D(const Vector3& wh) const;
//     float ggx_G1(const Vector3& w, const Vector3& n, float alpha) const;
//     float ggx_G(const Vector3& wi, const Vector3& wo, const Vector3& n, float alpha) const;

// private:
//     float roughness_;
//     float alpha_;

//     float etaI_ = 1.0f;
//     float etaT_ = 1.5f;
// };

// #endif