#ifndef _MIRROR_H_
#define _MIRROR_H_

#include "brdf.h"

class Mirror : public Brdf
{
public:
    Mirror();
    
    Color get_f(const Vector3 &wo, const Vector3 &wi) const override;

    Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const;
    virtual float pdf(const Vector3 &wo, const Vector3 &wi) const override;
    virtual std::shared_ptr<Brdf> clone() const override;
};

#endif