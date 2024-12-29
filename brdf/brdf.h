#ifndef _BRDF_H_
#define _BRDF_H_

#include <memory>

#include "color.h"
#include "vector.h"

class Brdf
{
public:
    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const = 0;
    virtual Color get_f(const Vector3 &wo, const Vector3 &wi) const;

    virtual float pdf(const Vector3 &wo, const Vector3 &wi) const;
    virtual std::shared_ptr<Brdf> clone() const = 0;

    const static Vector3 LOCAL_NORMAL;
};

#endif