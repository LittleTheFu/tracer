#include <cmath>
#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <sstream>

#include "common.h"
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

float Common::absCosTheta(const Vector3 &v)
{
    return std::abs(v.z);
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

    if (r == 0.0f)
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

    if (r == 0.0f)
        return 0.0f;

    return MathUtility::clamp(v.y / r, -1.0f, 1.0f);
}

float Common::sinPhiSq(const Vector3 &v)
{
    return sinPhi(v) * sinPhi(v);
}

float Common::fresnel(float etaI, float etaT, float cosThetaI)
{
    // 保证 cosThetaI 在 [0, 1] 范围内
    cosThetaI = std::max(0.0f, std::min(1.0f, cosThetaI));

    // 检查是否是从高折射率介质进入低折射率介质
    bool entering = cosThetaI > 0.f;
    float currentEtaI = etaI;
    float currentEtaT = etaT;
    if (!entering) { // 如果是从内部射出，交换折射率
        std::swap(currentEtaI, currentEtaT);
    }

    // 使用斯涅尔定律计算透射角的正弦值
    // eta_i * sin_i = eta_t * sin_t
    // sin_t = (eta_i / eta_t) * sin_i
    float sinThetaI = std::sqrt(std::max(0.0f, 1.0f - cosThetaI * cosThetaI));
    float sinThetaT = (currentEtaI / currentEtaT) * sinThetaI;

    // --- 检查全内反射 (Total Internal Reflection, TIR) ---
    // 只有当光从高折射率射向低折射率时才可能发生 (currentEtaI > currentEtaT)
    // 此时 sinThetaT 可能会大于 1.0
    if (sinThetaT >= 1.0f) {
        return 1.0f; // 所有光都被反射
    }

    // 计算透射角的余弦值
    // cos_t = sqrt(1 - sin_t^2)
    float cosThetaT = std::sqrt(std::max(0.0f, 1.0f - sinThetaT * sinThetaT));

    // --- 计算两个偏振分量的反射率 ---

    // 1. R_p (p-polarized: 平行于入射面的分量)
    // R_p = ((eta_t * cos_i - eta_i * cos_t) / (eta_t * cos_i + eta_i * cos_t))^2
    float rp_num = currentEtaT * cosThetaI - currentEtaI * cosThetaT;
    float rp_den = currentEtaT * cosThetaI + currentEtaI * cosThetaT;
    float Rp = (rp_den != 0.0f) ? (rp_num / rp_den) : 0.0f;

    // 2. R_s (s-polarized: 垂直于入射面的分量)
    // R_s = ((eta_i * cos_i - eta_t * cos_t) / (eta_i * cos_i + eta_t * cos_t))^2
    float rs_num = currentEtaI * cosThetaI - currentEtaT * cosThetaT;
    float rs_den = currentEtaI * cosThetaI + currentEtaT * cosThetaT;
    float Rs = (rs_den != 0.0f) ? (rs_num / rs_den) : 0.0f;
    
    // 对于非偏振光，反射率是两个分量反射率的平均值
    return (Rp * Rp + Rs * Rs) * 0.5f;
}

float Common::fresnel(float etaI,
                      float etaT,
                      float cos_theta_in,
                      float cos_theta_out)
{
    float r_pa = (etaT * cos_theta_in - etaI * cos_theta_out) /
                 (etaT * cos_theta_in + etaI * cos_theta_out);
    float r_per = (etaI * cos_theta_in - etaT * cos_theta_out) /
                  (etaI * cos_theta_in + etaT * cos_theta_out);

    return 0.5f * (r_pa * r_pa + r_per * r_per);
}

float Common::frenselComplex(std::complex<float> eta, float cos_theta_in)
{
    // eta = std::complex<float>(1) / eta;
    float sin2Theta_i = 1 - MathUtility::sq(cos_theta_in);
    std::complex<float> sin2Theta_t = sin2Theta_i / MathUtility::sq_c(eta);
    std::complex<float> cos_theta_t = std::sqrt(std::complex<float>(1) - sin2Theta_t);

    std::complex<float> r_pa = (eta * cos_theta_in - cos_theta_t) /
                               (eta * cos_theta_in + cos_theta_t);
    std::complex<float> r_per = (cos_theta_in - eta * cos_theta_t) /
                                (cos_theta_in + eta * cos_theta_t);

    return 0.5f * (getNormSq(r_pa) + getNormSq(r_per));
}

Color Common::FresnelConductor(float cosThetaI, const Color &eta, const Color &k)
{
    cosThetaI = MathUtility::clamp(cosThetaI, 0.0f, 1.0f);

    // Square terms
    float cos2 = cosThetaI * cosThetaI;
    Color eta2 = eta * eta;
    Color k2 = k * k;

    Color one(1.0f);
    Color sin2 = one - Color(cos2);

    Color t0 = eta2 - k2 - sin2;
    Color a2plusb2 = (t0 * t0 + eta2 * k2 * Color(4.0f, 4.0f, 4.0f));

    // sqrt(a^2 + b^2)
    Color a2plusb2Sqrt(std::sqrt(a2plusb2.r), std::sqrt(a2plusb2.g), std::sqrt(a2plusb2.b));

    // a = sqrt( (a2plusb2 + t0) / 2 )
    Color a = Color(
        std::sqrt(0.5f * (a2plusb2Sqrt.r + t0.r)),
        std::sqrt(0.5f * (a2plusb2Sqrt.g + t0.g)),
        std::sqrt(0.5f * (a2plusb2Sqrt.b + t0.b)));

    Color twoCosTheta = Color(2.0f * cosThetaI);

    // Rs
    Color Rs_num = a2plusb2Sqrt - (a * twoCosTheta);
    Color Rs_den = a2plusb2Sqrt + (a * twoCosTheta);
    Color Rs = (Rs_num / Rs_den);
    Rs = Rs * Rs; // (Rs)^2

    // Rp
    Color Rp_num = (a2plusb2Sqrt * Color(cos2)) - (a * Color(2.0f * cosThetaI) * sin2);
    Color Rp_den = (a2plusb2Sqrt * Color(cos2)) + (a * Color(2.0f * cosThetaI) * sin2);
    Color Rp = (Rp_num / Rp_den);
    Rp = Rp * Rp; // (Rp)^2

    return (Rs + Rp) * 0.5f;
}

float Common::getNormSq(std::complex<float> c)
{
    return c.real() * c.real() + c.imag() * c.imag();
}

bool Common::isBothTrue(bool a, bool b)
{
    return (a && b);
}

bool Common::isExactOneTrue(bool a, bool b)
{
    // xor is preferred but here just for clarity
    if (a && !b)
        return true;

    if (!a && b)
        return true;

    return false;
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