#ifndef _LAMBERTIAN_MATERIAL_H_
#define _LAMBERTIAN_MATERIAL_H_

#include "material.h"
#include "color.h"
// #include "brdf.h"
#include "lambertian.h"
#include "texture.h"

class LambertianMaterial : public Material
{
public:
    LambertianMaterial(const Texture *pTexture, float scale);

    Color eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const;

private:
    Lambertian *m_pLambertianBrdf;
    const Texture *m_pTexture;
};

#endif