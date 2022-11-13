#ifndef _LAMBERTIAN_MATERIAL_H_
#define _LAMBERTIAN_MATERIAL_H_

#include "material.h"
#include "color.h"
#include "brdf.h"
#include "texture.h"

class LambertianMaterial : public Material
{
public:
    LambertianMaterial(const Color &rho, const Texture *pTexture = nullptr);

    Color eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const;
};

#endif