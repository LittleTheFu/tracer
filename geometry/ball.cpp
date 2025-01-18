#include <algorithm>
#include <cmath>

#include "ball.h"
#include "common.h"
#include "frame.h"
#include "mathConstantDef.h"
#include "mathUtility.h"

Ball::Ball()
{
    this->r = 1;
}

Ball::Ball(const Vector3 &rotate, const Vector3 &position, float r, std::shared_ptr<Material> pMtrl)
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

Vector3 Ball::getLocalPoint(float theta, float phi) const
{
    float sinTheta = std::sin(theta);
    float cosTheta = std::cos(theta);

    float x = sinTheta * std::cos(phi);
    float y = sinTheta * std::sin(phi);
    float z = cosTheta;

    Vector3 v(x, y, z);
    v *= r;

    return v;
}

Vector3 Ball::getLocalDirection(float u, float v) const
{
    const float phi = u * MathConstant::TWO_PI;
    const float theta = v * MathConstant::PI;

    const float x = std::sin(theta) * std::cos(phi);
    const float y = std::sin(theta) * std::sin(phi);
    const float z = std::cos(theta);

    return Vector3(x, y, z);
}

Vector3 Ball::getCentroid() const
{
    return m_transform.transformPoint(Vector3::ZERO);
}

float Ball::surfaceArea() const
{
    return MathConstant::FOUR_PI * r * r;
}

void Ball::buildBoundBox()
{
    Vector3 pos = m_transform.transformPoint(Vector3::ZERO);
    Vector3 R(r, r, r);

    const Vector3 min = pos - R;
    const Vector3 max = pos + R;

    m_boundBox.update(min);
    m_boundBox.update(max);
}

bool Ball::testHit(const Ray &localRay, float &t) const
{
    float a, b, c;
    genRayHitParam(localRay, a, b, c);

    float t0, t1;
    if (!MathUtility::solveLinerEquation(a, b, c, t0, t1))
        return false;

    //refactor later...
    if (!getHitParam(t0, t1, t))
        return false;

    return true;
}

bool Ball::isIn(const Vector3 &point) const
{
    Vector3 center = m_transform.transformPoint(Vector3::ZERO);
    Vector3 diff = point - center;

    if (diff.lenthSqr() <= r * r)
    {
        return true;
    }

    return false;
}

bool Ball::hit(const Ray &ray, HitRecord &record) const
{
    const Ray newRay = ray.genNewRay(m_transform);

    if (!testHit(newRay, record.t))
        return false;

    record.transform = m_transform;

    const Vector3 localPoint = newRay.getPosition(record.t);
    record.point = m_transform.transformPoint(localPoint);
    record.localPoint = localPoint;

    Vector3 localNormal = getLocalNormal(localPoint);
    if(m_pMtrl && m_pMtrl->isNormalTextureValid()) //quick and dirty, only for test.localNomal should be renamed
    {
        localNormal = getNormalFromNormalMap(localNormal, localPoint);
    }
    record.normal = m_transform.transformNormal(localNormal);

    record.u = u(localPoint);
    record.v = v(localPoint);

    if (m_pMtrl)
    {
        HandleMaterial(localNormal, localPoint, newRay, record);
    }
    else
    {
        // for volume rendering(just for test now)
        record.isVolumeBoundery = true;
    }

    return true;
}

Vector3 Ball::sampleFromPoint(const Vector3 &thatPoint, float &pdf) const
{
    Vector3 localPoint = m_transform.invTransformPoint(thatPoint);
    Vector3 zAxisVector = -localPoint;

    Frame frame(zAxisVector, localPoint);
    Vector3 framePoint = Vector3::ZERO;

    float d = localPoint.length();
    float thetaMax = std::asin(r / d);
    float cosThetaMax = std::cos(thetaMax);

    float rnd = MathUtility::genRandomDecimal();
    float sampleCosTheta = 1 - rnd + rnd * cosThetaMax;
    float theta = std::acos(sampleCosTheta);

    float gamma = MathConstant::PI - d / r * std::sin(theta);
    float alpha = MathConstant::PI - gamma - theta;
    float phi = MathUtility::genRandomDecimal() * MathConstant::TWO_PI;

    Vector3 sampleZAxis(0, 0, -1);
    Vector3 sampleBallFrameOrigin(0, 0, d);
    Frame sampleBallFrame(sampleZAxis, sampleBallFrameOrigin);
    Vector3 sampledBallPoint = getLocalPoint(alpha, phi);

    sampledBallPoint = sampleBallFrame.pointToWorld(sampledBallPoint);
    sampledBallPoint = frame.pointToWorld(sampledBallPoint);

    Vector3 worldSampledPoint = m_transform.transformPoint(sampledBallPoint);

    float oneMinus = 1 - cosThetaMax;
    float div = 1 / oneMinus;
    pdf = div * MathConstant::INV_TWO_PI;

    return worldSampledPoint;
}

Vector3 Ball::dpdu(const Vector3 &point) const
{
    const float phi_max = MathConstant::PI * 2;

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
    const float theta_range = MathConstant::PI;

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
        phi += MathConstant::PI * 2;
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
    bool hit = t_min > MathConstant::FLOAT_SMALL_NUMBER;
    if (hit)
    {
        t_out = t_min;
    }
    else
    {
        hit = t_max > MathConstant::FLOAT_SMALL_NUMBER;
        if (hit)
        {
            t_out = t_max;
        }
    }

    return hit;
}

void Ball::HandleMaterial(const Vector3 &localNormal, const Vector3 &localPoint, const Ray &newRay, HitRecord &record) const
{
    Frame frame(localNormal, dpdu(localPoint), Vector3::ZERO);

    const Vector3 local_wo = frame.pointToLocal(-newRay.dir);
    Vector3 r;
    record.f = m_pMtrl->eval(record.u, record.v, local_wo, r, record.reflectPdf, record.isDelta, record.brdf);
    record.dot = MathUtility::clamp(std::abs(r * Common::LOCAL_NORMAL), MathConstant::FLOAT_SMALL_NUMBER, 1.0f);

    Vector3 localReflectVector = frame.pointToWorld(r);
    localReflectVector.normalize();
    record.reflect = m_transform.transformVector(localReflectVector);

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
    float uu = theta * MathConstant::INV_PI;

    return uu;
}

float Ball::v(const Vector3 &point) const
{
    float phi = getPhi(point);
    float vv = phi * MathConstant::INV_TWO_PI;

    return vv;
}