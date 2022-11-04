#include "vector.h"
#include <tgmath.h>
#include "common.h"
#include <cassert>

Vector3 const Vector3::ZERO = Vector3(0, 0, 0);

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

Vector3 Vector3::cross(const Vector3 &that) const
{
    float rX = y * that.z - z * that.y;
    float rY = z * that.x - x * that.z;
    float rZ = x * that.y - y * that.x;

    return Vector3(rX, rY, rZ);
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

Vector3 &Vector3::operator*=(float m)
{
    x *= m;
    y *= m;
    z *= m;

    return *this;
}

bool Vector3::operator==(const Vector3 &that) const
{
    bool eqX = Common::float_equal(this->x, that.x);
    bool eqY = Common::float_equal(this->y, that.y);
    bool eqZ = Common::float_equal(this->z, that.z);

    return (eqX && eqY && eqZ);
}

std::ostream &operator<<(std::ostream &os, const Vector3 &v)
{
    os << "(" << v.x << "," << v.y << "," << v.z << ")";

    return os;
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

bool Vector3::isZero() const
{
    return x == 0 && y == 0 && z == 0;
}

bool Vector3::isPerpendicular(const Vector3 &that) const
{
    const Vector3 r = this->cross(that);

    bool isX = std::abs(r.x) < Common::FLOAT_SAMLL_NUMBER;
    bool isY = std::abs(r.y) < Common::FLOAT_SAMLL_NUMBER;
    bool isZ = std::abs(r.z) < Common::FLOAT_SAMLL_NUMBER;

    return isX && isY && isZ;
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

Vector3 Vector3::getRandomVector()
{
    int x = std::rand() % 113 + 1;
    int y = std::rand() % 113 + 1;
    int z = std::rand() % 113 + 1;

    int a = std::rand() % 2;
    if (a != 0)
        x = -x;

    int b = std::rand() % 2;
    if (b != 0)
        y = -y;

    Vector3 v = Vector3(x, y, z);
    v.normalize();

    return v;
}

Vector3 Vector3::sampleUniformFromHemisphere()
{
    const float max = (float)RAND_MAX;
    const float u = std::rand() / max;
    const float v = std::rand() / max;

    const float cosTheta = u;
    const float sinTheta = std::sqrt(1 - cosTheta * cosTheta);
    const float phi = 2 * Common::PI * v;

    const float x = sinTheta * std::cos(phi);
    const float y = sinTheta * std::sin(phi);
    const float z = u;

    const Vector3 vec(x, y, z);
    const float lenthSqr = vec.lenthSqr();
    const float diff = lenthSqr - 1.0f;
    if (std::abs(diff) > Common::FLOAT_SAMLL_NUMBER)
    {
        // assert("vector is not normalized!");
    }

    return vec;
}

Vector3 Vector3::sampleUniformFromCone(float thetaMax)
{
    float u = Common::genRandomDecimal();
    float cosTheta = 1 - u + u * std::cos(thetaMax);
    float sinTheta = std::sqrt(1 - cosTheta * cosTheta);

    float v = Common::genRandomDecimal();
    float phi = v * Common::TWO_PI;

    float x = sinTheta * std::cos(phi);
    float y = sinTheta * std::sin(phi);
    float z = cosTheta;

    return Vector3(x, y, z);
}