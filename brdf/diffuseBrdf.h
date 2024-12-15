#ifndef _DIFFUSE_BRDF_H_
#define _DIFFUSE_BRDF_H_

#include "brdf.h"
#include "color.h"

class DiffuseBrdf : public Brdf
{
public:
    DiffuseBrdf(float scale);

    Color get_f(const Vector3 &wo, const Vector3 &wi) const override;

    Color sample_f(const Vector3 &wo, Vector3 &wi, float &pdf) const;
    void setColor(const Color &color);

    virtual float pdf(const Vector3 &wo, const Vector3 &wi) const override;


private:
    Color m_color;
    float m_scale;
};

#endif