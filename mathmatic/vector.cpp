#include "vector.h"
#include <tgmath.h>
#include <algorithm>
#include "mathUtility.h"
#include "mathConstantDef.h"
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

Vector3 Vector3::operator*(float m) const
{
    return Vector3(x * m, y * m, z * m);
}

Vector3 &Vector3::operator*=(float m)
{
    x *= m;
    y *= m;
    z *= m;

    return *this;
}

Vector3 Vector3::operator/(float m) const
{
    return Vector3(x / m, y / m, z / m);
}

Vector3 Vector3::div_component_wise(const Vector3 &that) const
{
    float x = this->x / that.x;
    float y = this->y / that.y;
    float z = this->z / that.z;

    return Vector3(x, y, z);
}

Vector3 Vector3::abs() const
{
    return Vector3(std::abs(x), std::abs(y), std::abs(z));
}

Vector3 Vector3::max_component_wise(const Vector3 &that) const
{
    float x = std::max(this->x, that.x);
    float y = std::max(this->y, that.y);
    float z = std::max(this->z, that.z);

    return Vector3(x, y, z);
}

Vector3 Vector3::min_component_wise(const Vector3 &that) const
{
    float x = std::min(this->x, that.x);
    float y = std::min(this->y, that.y);
    float z = std::min(this->z, that.z);

    return Vector3(x, y, z);
}

bool Vector3::less_or_equal_component_wise(const Vector3 &that) const
{
    bool bX = (x <= that.x);
    bool bY = (y <= that.y);
    bool bZ = (z <= that.z);

    return bX && bY && bZ;
}

Vector3 &Vector3::operator/=(float m)
{
    x /= m;
    y /= m;
    z /= m;

    return *this;
}

bool Vector3::operator==(const Vector3 &that) const
{
    bool eqX = MathUtility::is_float_equal(this->x, that.x);
    bool eqY = MathUtility::is_float_equal(this->y, that.y);
    bool eqZ = MathUtility::is_float_equal(this->z, that.z);

    return (eqX && eqY && eqZ);
}

bool Vector3::operator!=(const Vector3 &that) const
{
    return !(this->operator==(that));
}

float Vector3::operator[](int i) const
{
    if (i == 0)
        return x;
    if (i == 1)
        return y;
    if (i == 2)
        return z;

    assert(0);

    return x;
}

float &Vector3::operator[](int i)
{
    if (i == 0)
        return x;
    if (i == 1)
        return y;
    if (i == 2)
        return z;

    assert(0);

    return x;
}

std::ostream &operator<<(std::ostream &os, const Vector3 &v)
{
    os << "( " << v.x << ", " << v.y << ", " << v.z << " )";

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

Vector3 Vector3::dir() const
{
    float len = length();
    Vector3 v(0,0,0);

    if (len <= 0)
    {
        return v;
    }

    v = this->operator/(len);

    return v;
}

bool Vector3::isSameDir(const Vector3 & that) const
{
    float r = this->operator*(that);

    return r > 0;
}

Vector3 Vector3::reflect(const Vector3 &normal) const
{
    assert((normal != Vector3::ZERO) && "Vector3::reflect()");
    assert(!isSameDir(normal) && "Vector3::reflect()");

    Vector3 n = normal.dir();
    n.normalize();
    float m = -this->operator*(n);

    return 2 * m * n + (*this);
}

Vector3 Vector3::_refract(const Vector3 &normal,
                          float etaInputSide,
                          float etaOutputSide,
                          bool &totalReflect,
                          float &fresnel) const
{
    assert((normal != Vector3::ZERO && "Vector3::_refract"));
    assert((etaInputSide != 0) && "Vector3::_refract");
    assert((etaOutputSide != 0) && "Vector3::_refract");
    assert(!isSameDir(normal) && "Vector3::_refract");

    float eta = etaOutputSide / etaInputSide;

    Vector3 n = -normal;
    float nLen = n.length();
    float dot = this->operator*(n);

    float cos_theta_in_sqr = dot * dot;
    float sin_theta_in_sqr = 1 - cos_theta_in_sqr;
    bool is_sin_theta_sqr_in_range = MathUtility::is_in_range(sin_theta_in_sqr, 0, 1, true, true);
    // assert(is_sin_theta_sqr_in_range && "Vector3::_refract");

    float sin_theta_out_sqr = sin_theta_in_sqr / (eta * eta);
    if(sin_theta_out_sqr >= 1)
    {
        totalReflect = true;
        fresnel = 1;
        return reflect(normal);
    }

    bool is_sin_theta_out_sqr_in_range = MathUtility::is_in_range(sin_theta_out_sqr, 0, 1, true, false);
    // assert(is_sin_theta_out_sqr_in_range && "Vector3::_refract");

    float cos_theta_out_sqr = 1 - sin_theta_out_sqr;
    bool is_cos_theta_out_sqr = MathUtility::is_in_range(cos_theta_out_sqr, 0, 1, true, true);
    float cos_theta_out = sqrt(cos_theta_out_sqr);
   

    Vector3 in_n = (this->operator*(n)) * n;
    Vector3 in_p = this->operator-(in_n);
    Vector3 out_p = in_p / eta;
    Vector3 out_n = cos_theta_out * this->length() * n;

    Vector3 out = out_p + out_n;

    float cos_theta_in = dot;

    float r_pa = (etaOutputSide * cos_theta_in - etaInputSide * cos_theta_out) /
                 (etaOutputSide * cos_theta_in + etaInputSide * cos_theta_out);
    float r_per = (etaInputSide * cos_theta_in - etaOutputSide * cos_theta_out) /
                  (etaInputSide * cos_theta_in + etaOutputSide * cos_theta_out);

    fresnel = 0.5f * (r_pa * r_pa + r_per * r_per);

    return out;
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

    bool isX = std::abs(r.x) < MathConstant::FLOAT_SAMLL_NUMBER;
    bool isY = std::abs(r.y) < MathConstant::FLOAT_SAMLL_NUMBER;
    bool isZ = std::abs(r.z) < MathConstant::FLOAT_SAMLL_NUMBER;

    return isX && isY && isZ;
}

Vector3 Vector3::getTangentVector() const
{
    Vector3 r;

    int idx[3] = { -1, -1, -1};

    int j = 0;
    for(int i = 0; i < 3 ;i ++)
    {
        if(this->operator[](i) != 0.0f)
        {
            idx[j++] = i; 
        }
    }

    if(j == 0)
        return r;

    if (j == 1)
    {
        r[idx[0]] = 0;
        r[(idx[0] + 1) % 3] = this->operator[](idx[0]); 
        return r;
    }

    r[idx[0]] = -this->operator[](idx[1]);
    r[idx[1]] = this->operator[](idx[0]);
    
    return r;
}

float Vector3::length() const
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
    // int x = std::rand() % 113 + 1;
    // int y = std::rand() % 113 + 1;
    // int z = std::rand() % 113 + 1;

    // int a = std::rand() % 2;
    // if (a != 0)
    //     x = -x;

    // int b = std::rand() % 2;
    // if (b != 0)
    //     y = -y;

    // Vector3 v = Vector3(x, y, z);
    // v.normalize();

    // return v;
    return Vector3();
}

Vector3 Vector3::sampleUniformFromHemisphere()
{
    const float u = MathUtility::genRandomDecimal();
    const float v = MathUtility::genRandomDecimal();

    const float cosTheta = u;
    const float sinTheta = std::sqrt(1 - cosTheta * cosTheta);
    const float phi = 2 * MathConstant::PI * v;

    const float x = sinTheta * std::cos(phi);
    const float y = sinTheta * std::sin(phi);
    const float z = u;

    const Vector3 vec(x, y, z);

    return vec;
}

Vector3 Vector3::sampleUniformFromSphere()
{
    const float max = (float)RAND_MAX;

    const float u = MathUtility::genRamdomSignDecimal();
    const float v = MathUtility::genRandomDecimal();

    const float cosTheta = u;
    const float sinTheta = std::sqrt(1 - cosTheta * cosTheta);
    const float phi = 2 * MathConstant::PI * v;

    const float x = sinTheta * std::cos(phi);
    const float y = sinTheta * std::sin(phi);
    const float z = u;

    const Vector3 vec(x, y, z);

    return vec;
}

Vector3 Vector3::sampleUniformFromCone(float thetaMax)
{
    float u = MathUtility::genRandomDecimal();
    float cosTheta = 1 - u + u * std::cos(thetaMax);
    float sinTheta = std::sqrt(1 - cosTheta * cosTheta);

    float v = MathUtility::genRandomDecimal();
    float phi = v * MathConstant::TWO_PI;

    float x = sinTheta * std::cos(phi);
    float y = sinTheta * std::sin(phi);
    float z = cosTheta;

    return Vector3(x, y, z);
}