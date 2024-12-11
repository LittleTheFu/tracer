#ifndef _LAMBERTIAN_MATERIAL_H_
#define _LAMBERTIAN_MATERIAL_H_

#include "material.h"
#include "color.h"
// #include "brdf.h"
#include "lambertian.h"
#include "texture.h"
#include <memory>

class LambertianMaterial : public Material
{
public:
    LambertianMaterial(std::shared_ptr<const Texture> pTexture, float scale);

    Color get_f(const Vector3 &wo, const Vector3 &wi) const;
    virtual Color eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const;

private:
    std::shared_ptr<Lambertian> m_pLambertianBrdf;
    std::shared_ptr<const Texture> m_pTexture;
};

#endif