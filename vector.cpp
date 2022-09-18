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

Vector3 Vector3::operator+(const Vector3 &that)
{
    float x = this->x + that.x;
    float y = this->y + that.y;
    float z = this->z + that.z;

    return Vector3(x, y, z);
}

float Vector3::operator*(const Vector3 &that)
{
    float x = this->x * that.x;
    float y = this->y * that.y;
    float z = this->z * that.z;

    return x + y + z;
}

void Vector3::normalize()
{
    float len = length();

    x /= len;
    y /= len;
    z /= len;
}

float Vector3::length()
{
    float xSqr = x * x;
    float ySqr = y * y;
    float zSqr = z * z;

    float lenSqr = xSqr + ySqr + zSqr;

    return sqrt(lenSqr);
}