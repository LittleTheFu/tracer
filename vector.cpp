#include "vector.h"
#include <tgmath.h>

Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3 Vector3::operator+(const Vector3 &that) const
{
    float x = this->x + that.x;
    float y = this->y + that.y;
    float z = this->z + that.z;

    return Vector3(x, y, z);
}

Vector3 Vector3::operator-(const Vector3 &that) const
{
    float x = this->x - that.x;
    float y = this->y - that.y;
    float z = this->z - that.z;

    return Vector3(x, y, z);
}

float Vector3::operator*(const Vector3 &that) const
{
    float x = this->x * that.x;
    float y = this->y * that.y;
    float z = this->z * that.z;

    return x + y + z;
}

Vector3 operator*(const float s, const Vector3 &v)
{
    float x = v.x * s;
    float y = v.y * s;
    float z = v.z * s;

    return Vector3(x, y, z);
}

Vector3 Vector3::operator-() const
{
    float x = -this->x;
    float y = -this->y;
    float z = -this->z;

    return Vector3(x, y, z);
}

float Vector3::lenthSqr() const
{
    float xSqr = x * x;
    float ySqr = y * y;
    float zSqr = z * z;

    return xSqr + ySqr + zSqr;
}

void Vector3::normalize()
{
    float len = length();

    if (len <= 0)
    {
        x = 0;
        y = 0;
        z = 0;

        return;
    }

    x /= len;
    y /= len;
    z /= len;
}

Vector3 Vector3::reflect(const Vector3 &normal) const
{
    Vector3 n = normal;
    n.normalize();

    float m = -this->operator*(n);
    // if (m < 0)
    // {
    //     n = -n;
    //     m = -m;
    // }

    return 2 * m * n + (*this);
}

bool Vector3::isInSameSide(const Vector3 &that) const
{
    const float result = this->operator*(that);

    return result > 0;
}

float Vector3::length()
{
    float lenSqr = lenthSqr();
    if (lenSqr <= 0.0f)
    {
        return 0.0f;
    }

    return sqrt(lenSqr);
}