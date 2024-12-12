#ifndef _MIRROR_H_
#define _MIRROR_H_

#include "brdf.h"

class Mirror : public Brdf
{
public:
    Mirror();
    
    Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const;
};

#endif