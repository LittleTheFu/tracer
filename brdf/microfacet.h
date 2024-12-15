#ifndef _MICROFACET_H_
#define _MICROFACET_H_

#include "vector.h"

class Microfacet
{
public:
    Microfacet(float alpha_x, float alpha_y);

    float distribution(const Vector3 &wm) const;
    bool isSmooth() const;
    float lambda(const Vector3 &w) const;
    float g(const Vector3 &wo, const Vector3 &wi) const;
    float g1(const Vector3 &w) const;
    float d(const Vector3 &w, const Vector3 &wm) const;

    Vector3 sample_wm(const Vector3 &w) const;
    float pdf(const Vector3 &wo, const Vector3 &wi) const;
   
private:
    float m_alpha_x;
    float m_alpha_y;

};

#endif