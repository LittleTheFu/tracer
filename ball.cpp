#include "ball.h"
#include "common/common.h"
#include <cmath>
#include <algorithm>
#include "frame.h"

Ball::Ball()
{
    this->r = 1;
    this->m_pMtrl = nullptr;
}

Ball::Ball(const Vector3 &rotate, const Vector3 &position, float r, Material *pMtrl)
{
    init(rotate, position);

    this->r = r;
    this->m_pMtrl = pMtrl;
}

Vector3 Ball::getLocalNormal(const Vector3 &thatPoint) const
{
    Vector3 normal = thatPoint;
    normal.normalize();

    return normal;
}

Vector3 Ball::getLocalDirection(float u, float v) const
{
    const float phi = u * Common::TWO_PI;
    const float theta = v * Common::PI;

    const float x = std::sin(theta) * std::cos(phi);
    const float y = std::sin(theta) * std::sin(phi);
    const float z = std::cos(theta);

    return Vector3(x, y, z);
}

Color Ball::get_f(const Vector3 &wo, const Vector3 &wi, const Vector3 &point, const Vector3 &normal) const
{
    return Color::COLOR_WHITE;
}

bool Ball::hit(const Ray &ray, HitRecord &record, Light *pLight) const
{
    // record.t = Common::FLOAT_MAX;

    const Ray newRay = ray.genNewRay(m_transform);

    float a, b, c;
    genRayHitParam(newRay, a, b, c);

    float t0, t1;
    if (!Common::solveLinerEquation(a, b, c, t0, t1))
        return false;

    bool hit = getHitParam(t0, t1, record.t);

    if (!hit)
        return false;

    record.transform = m_transform;

    const Vector3 localPoint = newRay.origin + record.t * newRay.dir;
    record.point = m_transform.transformPoint(localPoint);

    const Vector3 localNormal = getLocalNormal(localPoint);
    record.normal = m_transform.transformNormal(localNormal);

    record.u = u(localPoint);
    record.v = v(localPoint);

    if (m_pMtrl)
    {
        HandleMaterial(localNormal, localPoint, newRay, record);
    }

    return true;
}

Vector3 Ball::sampleFromPoint(const Vector3 &thatPoint, float &pdf) const
{
    Vector3 localPoint = m_transform.invTransformPoint(thatPoint);
    Vector3 localNormal = getLocalNormal(localPoint);

    Frame frame(localNormal, dpdu(thatPoint));
    Vector3 framePoint = frame.toLocal(localPoint);

    float d = framePoint.z;
    float alpha = std::asin(r / d);

    float thetaMax = Common::PI - alpha;
    Vector3 dir = Vector3::sampleUniformFromCone(thetaMax);
    Vector3 sampledFramePoint = r * dir;
    sampledFramePoint *= Common::SAMPLE_LIGHTR_CORRECT_FACTOR;

    Vector3 localSampledPoint = frame.toWorld(sampledFramePoint);

    Vector3 worldSampledPoint = m_transform.transformPoint(localSampledPoint);

    pdf = (1 / (1 - std::cos(thetaMax))) * Common::INV_TWO_PI;
    return worldSampledPoint;
}

Vector3 Ball::dpdu(const Vector3 &point) const
{
    const float phi_max = Common::PI * 2;

    const float x = -point.y * phi_max;
    const float y = point.x * phi_max;
    const float z = 0;

    Vector3 v = Vector3(x, y, z);
    v.normalize();

    return v;
}

Vector3 Ball::dpdv(const Vector3 &point) const
{
    const float phi = getPhi(point);
    const float theta_range = Common::PI;

    const float theta = getTheta(point);

    const float x = point.z * std::cos(phi) * theta_range;
    const float y = point.z * std::sin(phi) * theta_range;
    const float z = -std::sin(theta) * theta_range;

    Vector3 v = Vector3(x, y, z);
    v.normalize();

    return v;
}

float Ball::getPhi(const Vector3 &point) const
{
    float phi = std::atan2(point.y, point.x);
    if (phi < 0)
    {
        phi += Common::PI * 2;
    }

    return phi;
}

float Ball::getTheta(const Vector3 &point) const
{
    float a = point.z / r;
    if (a < -1)
        a = -1;
    if (a > 1)
        a = 1;

    const float theta = std::acos(point.z / r);

    return theta;
}

bool Ball::getHitParam(float t_min, float t_max, float &t_out) const
{
    bool hit = t_min > Common::FLOAT_SAMLL_NUMBER;
    if (hit)
    {
        t_out = t_min;
    }
    else
    {
        hit = t_max > Common::FLOAT_SAMLL_NUMBER;
        if (hit)
        {
            t_out = t_max;
        }
    }

    return hit;
}

void Ball::HandleMaterial(const Vector3 &localNormal, const Vector3 &localPoint, const Ray& newRay, HitRecord &record) const
{
    record.mtrl = *m_pMtrl;
    record.isDelta = m_pMtrl->isDelta();

    Frame frame(localNormal, dpdu(localPoint));

    const Vector3 local_wo = frame.toLocal(-newRay.dir);
    Vector3 r;
    record.f = m_pMtrl->eval(record.u, record.v, local_wo, r, record.reflectPdf);
    record.dot = Common::clamp(std::abs(r * Common::LOCAL_NORMAL), Common::FLOAT_SAMLL_NUMBER, 1.0f);

    Vector3 localReflectVector = frame.toWorld(r);
    localReflectVector.normalize();
    record.reflect = m_transform.transformVector(localReflectVector);
    record.isMirror = m_pMtrl->isMirror();

    if (record.isDelta)
    {
        record.dot = 1;
    }
}

void Ball::genRayHitParam(const Ray &ray, float &a_out, float &b_out, float &c_out) const
{
    a_out = ray.dir.lenthSqr();
    b_out = 2 * (ray.dir * ray.origin);
    c_out = ray.origin.lenthSqr() - r * r;
}

float Ball::u(const Vector3 &point) const
{
    float theta = getTheta(point);
    float uu = theta * Common::INV_PI;

    return uu;
}

float Ball::v(const Vector3 &point) const
{
    float phi = getPhi(point);
    float vv = phi * Common::INV_TWO_PI;

    return vv;
}