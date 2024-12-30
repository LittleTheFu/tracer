#ifndef _COMBINED_MATERIAL_H_
#define _COMBINED_MATERIAL_H_

#include "material.h"
#include <memory>

class CombinedMaterial : public Material
{
public:
    CombinedMaterial() = delete;
    CombinedMaterial(std::shared_ptr<Material> first, std::shared_ptr<Material> second, float weight);

    virtual Color eval(float u,
                       float v,
                       const Vector3 &wo,
                       Vector3 &wi,
                       float &pdf,
                       bool &isDelta,
                       std::shared_ptr<Brdf> &brdf) override;

private:
    std::shared_ptr<Material> m_FirstMaterial;
    std::shared_ptr<Material> m_SecondMaterial;

    std::shared_ptr<Material> m_currentMaterial;//bad,to be fixed later

    //should be renamed to a better name
    float m_weight;
};

#endif