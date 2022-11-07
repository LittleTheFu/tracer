#ifndef _GLASS_H_
#define _GLASS_H_

#include "brdf.h"

class Glass : public Brdf
{
public:
    Glass();

    Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf);
    bool isGlass() const;
};

#endif