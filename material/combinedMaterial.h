#ifndef _COMBINED_MATERIAL_H_
#define _COMBINED_MATERIAL_H_

#include "material.h"
#include <memory>

class CombinedMaterial : public Material
{
public:
    CombinedMaterial() = delete;
    CombinedMaterial(std::shared_ptr<Material> first, std::shared_ptr<Material> second);

    virtual Color get_f(const Vector3 &wo, const Vector3 &wi) const override;
    virtual Color eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta) override;

private:
    std::shared_ptr<Material> m_FirstMaterial;
    std::shared_ptr<Material> m_SecondMaterial;

    std::shared_ptr<Material> m_currentMaterial;//bad,to be fixed later

    //should be renamed to a better name
    float m_factor;
};

#endif