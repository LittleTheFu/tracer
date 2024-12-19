#ifndef _R_MATERIAL_H_
#define _R_MATERIAL_H_

#include "brdf.h"
#include "color.h"
#include "ray.h"
#include "texture.h"
#include "vector.h"
#include <memory>

class Material
{
public:
    Material();

    virtual Color eval(float u,
                       float v,
                       const Vector3 &wo,
                       Vector3 &wi,
                       float &pdf,
                       bool &isDelta,
                       std::shared_ptr<Brdf> &brdf);
};

#endif