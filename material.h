#ifndef _R_MATERIAL_H_
#define _R_MATERIAL_H_

#include "brdf.h"
#include "color.h"
#include "ray.h"

class Material
{
public:
    // void eval(const HitInfo &info);
    Color calc(const Color &inputColor, const Ray &inputDir) const;
    Brdf *pBrdf;
};

#endif