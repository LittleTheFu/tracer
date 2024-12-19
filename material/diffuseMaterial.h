#ifndef _DIFFUSE_MATERIAL_H_
#define _DIFFUSE_MATERIAL_H_

#include "material.h"
#include "color.h"
// #include "brdf.h"
#include "diffuseBrdf.h"
#include "texture.h"
#include <memory>

class DiffuseMaterial : public Material
{
public:
    DiffuseMaterial(std::shared_ptr<Texture> pTexture, float scale);

    virtual Color eval(float u,
                       float v,
                       const Vector3 &wo,
                       Vector3 &wi,
                       float &pdf,
                       bool &isDelta,
                       std::shared_ptr<Brdf> &brdf);

private:
    std::shared_ptr<DiffuseBrdf> m_pDiffuseBrdf;
    std::shared_ptr<const Texture> m_pTexture;
};

#endif