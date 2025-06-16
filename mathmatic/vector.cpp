#include <algorithm>
#include <cassert>

#include "common.h"
#include "mathConstantDef.h"
#include "mathUtility.h"
#include "vector.h"

Vector3 const Vector3::ZERO = Vector3(0, 0, 0);
Vector3 const Vector3::ONE = Vector3(1, 1, 1);

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

float Vector3::lenthSq() const
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
    assert(!this->isZero());
    assert(!that.isZero());

    float r = this->operator*(that);

    return r > 0;
}

Vector3 Vector3::conductorReflect(const Vector3 &normal, std::complex<float> etaOutside, std::complex<float> etaInside, float &fresnel) const
{
    return Vector3();
}

// 在 Vector3.cpp 或定义 Vector3::reflect 的位置
Vector3 Vector3::reflect(const Vector3 &normal_raw) const
{
    assert((normal_raw != Vector3::ZERO) && "Vector3::reflect() - Normal is zero.");
    assert(!this->isSameDir(normal_raw));

    Vector3 n = normal_raw.dir();
    float dot_prod = this->operator*(n); 

    return *this - 2 * dot_prod * n; 
}

// Vector3 Vector3::reflect(const Vector3 &normal) const
// {
//     assert((normal != Vector3::ZERO) && "Vector3::reflect()");
//     assert(!isSameDir(normal) && "Vector3::reflect()");

//     Vector3 n = normal.dir();
//     n.normalize();
//     float m = -this->operator*(n);

//     return 2 * m * n + (*this);
// }

Vector3 Vector3::refract(const Vector3 &normal,
                         float etaI,
                         float etaT,
                         bool &totalReflect,
                         float &fresnel) const
{
    totalReflect = false;
    
    assert((normal != Vector3::ZERO && "Vector3::_refract"));
    assert((etaI != 0) && "Vector3::_refract");
    assert((etaT != 0) && "Vector3::_refract");

    // 原始的向外法线 (N_outward)
    // Vector3 N_outward = normal.dir(); 

    // 计算入射光线与向外法线的点积
    // float cos_theta_incident_raw = (*this) * N_outward; 

    // 根据光线是进入还是离开，调整内部使用的折射率和法线方向
    float current_etaI = etaI; 
    float current_etaT = etaT; 
    // Vector3 n_internal; 

    // if (cos_theta_incident_raw < 0) { // 光线正在进入物体 (例如，从空气到玻璃)
    //     n_internal = N_outward; 
    // } else { // 光线正在离开物体 (例如，从玻璃到空气)
    //     n_internal = -N_outward; 
    //     // std::swap(current_etaI, current_etaT); 
    // }

    // 现在，'dot' (cos_theta_i) 始终是负值，符合标准折射公式的预期
    // float dot = (*this) * n_internal; 
    float dot = (*this) * normal; 
    
    float cos_theta_in_sqr = dot * dot;
    float sin_theta_in_sqr = 1.0f - cos_theta_in_sqr;
    if (sin_theta_in_sqr < 0.0f) sin_theta_in_sqr = 0.0f; 

    float eta_ratio = current_etaI / current_etaT; 

    float sin_theta_out_sqr = sin_theta_in_sqr * (eta_ratio * eta_ratio);
    
    if(sin_theta_out_sqr >= 1.0f - MathConstant::FLOAT_SMALL_NUMBER) // 使用 epsilon
    {
        totalReflect = true;
        fresnel = 1;
        // 反射时，法线需要指向远离入射光线的方向
        // return reflect(cos_theta_incident_raw < 0 ? N_outward : -N_outward); 
        return reflect(normal);
    }

    if (sin_theta_out_sqr > 1.0f) sin_theta_out_sqr = 1.0f; // 钳位
    float cos_theta_out_sqr = 1.0f - sin_theta_out_sqr;
    if (cos_theta_out_sqr < 0.0f) cos_theta_out_sqr = 0.0f; // 钳位
    float cos_theta_out = sqrt(cos_theta_out_sqr);
    
    // --- 调试输出 (cos_theta_i) ---
    // std::cout << "DEBUG: cos_theta_i (from dot) = " << dot << std::endl; 

    // *** 新的折射向量计算方法 ***
    // T_perp = eta * I_perp
    // I_perp = I - (I . N_in) * N_in = I - dot * N_in
    Vector3 T_perp = eta_ratio * ((*this) - dot * normal); 

    // T_parallel = -cos_theta_out * N_in
    Vector3 T_parallel = -cos_theta_out * normal;

    // 最终折射向量 T = T_perp + T_parallel
    Vector3 out = T_perp + T_parallel;

    // --- 调试输出 (out.length()) ---
    // std::cout << "DEBUG: out.length() before final return = " << out.length() << std::endl;

    // 菲涅尔计算 (注意传入 cos_theta_in 的绝对值)
    float cos_theta_in_fresnel = std::abs(dot); 
    fresnel = Common::fresnel(current_etaI, current_etaT, cos_theta_in_fresnel, cos_theta_out);

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
    float dot_product = (*this) * that;
    return MathUtility::is_float_equal(dot_product, 0.0f);
}

void Vector3::faceForward(const Vector3 &forward)
{
    float dot = this->operator*(forward);

    if (dot < 0)
    {
        *this = -(*this);
    }
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
    float lenSqr = lenthSq();
    if (lenSqr <= 0.0f)
    {
        return 0.0f;
    }

    return sqrt(lenSqr);
}

Vector3 Vector3::getRandomVector()
{
    Vector3 vec(MathUtility::genRandomDecimal(), MathUtility::genRandomDecimal(), MathUtility::genRandomDecimal());
    vec.normalize();

    return vec;
}

Vector3 Vector3::sampleUniformFromHemisphere()
{
    const float r1 = MathUtility::genRandomDecimal();
    const float r2 = MathUtility::genRandomDecimal();

    const float cosTheta = r1;
    const float sinTheta = std::sqrt(1 - cosTheta * cosTheta);
    const float phi = 2 * MathConstant::PI * r2;

    const float x = sinTheta * std::cos(phi);
    const float y = sinTheta * std::sin(phi);
    const float z = r1;

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