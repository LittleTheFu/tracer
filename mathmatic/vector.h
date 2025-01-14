#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <complex>

class Vector3
{
public:
    Vector3();
    Vector3(float x, float y, float z);

    Vector3 cross(const Vector3 &that) const;

    Vector3 operator+(const Vector3 &that) const;
    Vector3 operator-(const Vector3 &that) const;
    Vector3 operator-() const;
    float operator*(const Vector3 &that) const;
    Vector3 operator*(float m) const;
    Vector3 &operator*=(float m);
    Vector3 operator/(float m) const;
    Vector3 &operator/=(float m);
    friend Vector3 operator*(const float s, const Vector3 &v);

    Vector3 abs() const;

    Vector3 div_component_wise(const Vector3 &that) const;
    Vector3 max_component_wise(const Vector3 &that) const;
    Vector3 min_component_wise(const Vector3 &that) const;
    bool less_or_equal_component_wise(const Vector3 &that) const;

    bool operator==(const Vector3 &that) const;
    bool operator!=(const Vector3 &that) const;

    float operator[](int i) const;
    float &operator[](int i);

    friend std::ostream &operator<<(std::ostream &os, const Vector3 &v);

    bool isZero() const;
    bool isPerpendicular(const Vector3 &that) const;

    void faceForward(const Vector3 &forward);
    Vector3 getTangentVector() const;

    float length() const;
    float lenthSqr() const;
    void normalize();
    Vector3 dir() const;

    bool isSameDir(const Vector3 & that) const;

    Vector3 conductorReflect(const Vector3 &normal,
                             std::complex<float> etaOutside,
                             std::complex<float> etaInside,
                             float &fresnel) const;

    Vector3 reflect(const Vector3 &normal) const;
    Vector3 refract(const Vector3 &normal,
                     float etaOutside,
                     float etaInside,
                     bool &totalReflect,
                     float &fresnel) const;
    bool isInSameSide(const Vector3 &that) const;

    static Vector3 getRandomVector();
    static Vector3 sampleUniformFromHemisphere();
    static Vector3 sampleUniformFromSphere();
    static Vector3 sampleUniformFromCone(float thetaMax);

    static const Vector3 ZERO;
    static const Vector3 ONE;

    float x;
    float y;
    float z;
};

#endif