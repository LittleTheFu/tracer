#ifndef _MEASURED_MATERIAL_H_
#define _MEASURED_MATERIAL_H_

#include "material.h"
#include "measuredBrdf.h"
#include <memory>
#include <string>

class MeasuredMaterial : public Material
{
public:
    MeasuredMaterial(const std::string &brdfPath);

    virtual Color eval(float u,
                       float v,
                       const Vector3 &wo,
                       Vector3 &wi,
                       float &pdf,
                       bool &isDelta,
                       std::shared_ptr<Brdf> &brdf) override;

private:
    std::shared_ptr<MeasuredBrdf> m_brdf;
};

#endif