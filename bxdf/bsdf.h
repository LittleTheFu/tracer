#ifndef _BSDF_H_
#define _BSDF_H_

#include "vector.h"
#include <memory>
#include <vector>
#include "bxdf.h"
#include "bxdfType.h"
#include "frame.h"


class Bsdf
{
public:
    Bsdf(const Vector3 &ns_world);

    void addBxdf(std::shared_ptr<Bxdf> bxdf);

    Color f(const Vector3 &wo, const Vector3 &wi, BxdfType flags) const;
    float pdf(const Vector3 &wo, const Vector3 &wi, BxdfType flags) const;

    Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction, BxdfType flags) const;


private:
    Vector3 nsWorld_;

    Vector3 tLocal_, bLocal_, nLocal_;
    Frame tbnFrame_;

    std::vector<std::shared_ptr<Bxdf>> bxdfs_;
};

#endif