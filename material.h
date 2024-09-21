#ifndef _R_MATERIAL_H_
#define _R_MATERIAL_H_

#include "brdf.h"
#include "color.h"
#include "ray.h"
#include "texture.h"
#include "vector.h"

class Material
{
public:
    Material();

    virtual Color get_f(const Vector3 &wo, const Vector3 &wi) const;

    virtual Color eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const;
    virtual bool isMirror() const;

    virtual bool isDelta() const;
};

#endif