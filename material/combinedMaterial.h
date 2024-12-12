#ifndef _COMBINED_MATERIAL_H_
#define _COMBINED_MATERIAL_H_

#include "material.h"
#include <memory>

class CombinedMaterial : public Material
{
public:
    CombinedMaterial() = delete;
    CombinedMaterial(std::shared_ptr<const Material> first, std::shared_ptr<const Material> second);

    virtual Color eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta) const override;

private:
    std::shared_ptr<const Material> m_FirstMaterial;
    std::shared_ptr<const Material> m_SecondMaterial;

    std::shared_ptr<const Material> m_currentMaterial;

    //should be renamed to a better name
    float m_factor;
};

#endif