#ifndef _COMMON_H_
#define _COMMON_H_

#include <complex>

#include "color.h"
#include "vector.h"

class Common
{
public:
    static Vector3 getNormal(const Vector3 &from, const Vector3 &to);

    //warning: input vector must be normalized,to be recosidered later...
    static float cosTheta(const Vector3 &v);
    static float cosThetaSq(const Vector3 &v);
    static float absCosTheta(const Vector3 &v);

    static float sinTheta(const Vector3 &v);
    static float sinThetaSq(const Vector3 &v);

    static float tanTheta(const Vector3 &v);
    static float tanThetaSq(const Vector3 &v);

    static float cosPhi(const Vector3 &v);
    static float cosPhiSq(const Vector3 &v);

    static float sinPhi(const Vector3 &v);
    static float sinPhiSq(const Vector3 &v);

    static float fresnel(float etaInputSide,
                         float etaOutputSide,
                         float cos_theta_in,
                         float cos_theta_out);

    static float frenselComplex(std::complex<float> eta, float cos_theta_in);
                
    static float getNormSq(std::complex<float> c);

    static bool isBothTrue(bool a, bool b);
    static bool isOnlyOneTrue(bool a, bool b);

public:
    static void printCurrentTime();

    const static Vector3 LOCAL_NORMAL;
};

#endif