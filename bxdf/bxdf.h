#ifndef _BXDF_H_
#define _BXDF_H_

#include "bxdfType.h"
#include "vector.h"
#include <color.h>
#include "interaction.h"

class Bxdf
{
public:
    virtual Color f(const Vector3 &wo, const Vector3 &wi) const = 0;
    virtual float pdf(const Vector3 &wo, const Vector3 &wi) const = 0;

    virtual Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const;

public:
    Bxdf(BxdfType type);
    virtual ~Bxdf() = default;

    BxdfType getType() const;
    bool isType(BxdfType type) const;

private:
    BxdfType type_;
};

#endif