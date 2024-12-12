#ifndef _DUMMY_MATERIAL_H_
#define _DUMMY_MATERIAL_H_

#include "material.h"

class DummyMaterial : public Material
{
public:
    virtual Color eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta);
};

#endif