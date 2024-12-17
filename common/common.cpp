#include "common.h"
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <sstream> 
#include <iomanip>
#include "mathConstantDef.h"
#include "mathUtility.h"

const Vector3 Common::LOCAL_NORMAL = Vector3(0, 0, 1);

Vector3 Common::getNormal(const Vector3 &from, const Vector3 &to)
{
    Vector3 r = to - from;
    r.normalize();

    return r;
}

float Common::cosTheta(const Vector3 &v)
{
    return v.z;
}

float Common::cosThetaSq(const Vector3 &v)
{
    return cosTheta(v) * cosTheta(v);
}

float Common::sinTheta(const Vector3 &v)
{
    return MathUtility::clamp(std::sqrt(sinThetaSq(v)), 0, 1);
}

float Common::sinThetaSq(const Vector3 &v)
{
    return MathUtility::clamp(1 - cosThetaSq(v), 0, 1);
}

float Common::tanTheta(const Vector3 &v)
{
    return sinTheta(v) / cosTheta(v);
}

float Common::tanThetaSq(const Vector3 &v)
{
    return sinThetaSq(v) / cosThetaSq(v);
}

float Common::cosPhi(const Vector3 &v)
{
    float r = sinTheta(v);

    if(r == 0.0f)
        return 1.0f;

    return MathUtility::clamp(v.x / r, -1.0f, 1.0f);
}

float Common::cosPhiSq(const Vector3 &v)
{
    return cosPhi(v) * cosPhi(v);
}

float Common::sinPhi(const Vector3 &v)
{
    float r = sinTheta(v);

    if(r == 0.0f)
        return 0.0f;

    return MathUtility::clamp(v.y / r, -1.0f, 1.0f);
}

float Common::sinPhiSq(const Vector3 &v)
{
    return sinPhi(v) * sinPhi(v);
}

float Common::fresnel(float etaInputSide,
                                          float etaOutputSide,
                                          float cos_theta_in,
                                          float cos_theta_out)
{
    float r_pa = (etaOutputSide * cos_theta_in - etaInputSide * cos_theta_out) /
                 (etaOutputSide * cos_theta_in + etaInputSide * cos_theta_out);
    float r_per = (etaInputSide * cos_theta_in - etaOutputSide * cos_theta_out) /
                  (etaInputSide * cos_theta_in + etaOutputSide * cos_theta_out);

    return 0.5f * (r_pa * r_pa + r_per * r_per);
}

void Common::printCurrentTime()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm;

#if defined(_WIN32)
    if (localtime_s(&local_tm, &now_time_t) != 0)
    {
        std::cerr << "Error calling localtime_s" << std::endl;
        return;
    }
#else
    if (localtime_r(&now_time_t, &local_tm) == nullptr)
    {
        std::cerr << "Error calling localtime_r" << std::endl;
        return;
    }
#endif

    std::cout << "Current time: " << std::put_time(&local_tm, "%H:%M:%S") << std::endl;
}