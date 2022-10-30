#ifndef _VECTOR_H_
#define _VECTOR_H_

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
    friend Vector3 operator*(const float s, const Vector3 &v);
    bool operator==(const Vector3 &that) const;

    bool isZero() const;
    bool isPerpendicular(const Vector3 &that) const;

    float length();
    float lenthSqr() const;
    void normalize();

    Vector3 reflect(const Vector3 &normal) const;
    bool isInSameSide(const Vector3 &that) const;

    static Vector3 getRandomVector();
    static Vector3 sampleUniformFromHemisphere();

    static const Vector3 ZERO;

    float x;
    float y;
    float z;
};

#endif