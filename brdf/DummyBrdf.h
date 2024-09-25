#ifndef _DUMMY_BRDF_H_
#define _DUMMY_BRDF_H_

#include "brdf.h"

class DummyBrdf : public Brdf
{
public:
    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) = 0;
};

#endif