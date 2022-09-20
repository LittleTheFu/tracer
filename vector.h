#ifndef _VECTOR_H_
#define _VECTOR_H_

class Vector3
{
public:
    Vector3();
    Vector3(float x, float y, float z);

    Vector3 operator+(const Vector3 &that) const;
    Vector3 operator-(const Vector3 &that) const;
    Vector3 operator-() const;
    float operator*(const Vector3 &that) const;
    friend Vector3 operator*(const float s, const Vector3& v);

    float lenthSqr() const;
    void normalize();

    Vector3 reflect(const Vector3 &normal) const;

    float x;
    float y;
    float z;

private:
    float length();
};

#endif