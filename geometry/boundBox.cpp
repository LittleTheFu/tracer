#include "boundBox.h"
#include <algorithm>
#include "common.h"

BoundBox::BoundBox()
{
    reset();
}

BoundBox::BoundBox(const Vector3 &p1, const Vector3 &p2)
{
    set(p1, p2);
}

void BoundBox::reset()
{
    float negInf = Common::FLOAT_NEGETIVE_INFINITY;
    float posInf = Common::FLOAT_POSITIVE_INFINITY;

    minPoint = Vector3(posInf, posInf, posInf);
    maxPoint = Vector3(negInf, negInf, negInf);
}

Vector3 BoundBox::getCenter() const
{
    Vector3 center = ( minPoint + maxPoint ) / 2;

    return center;
}

float BoundBox::getExtent(BoundBox::Axis axis) const
{
    Vector3 extent = (maxPoint - minPoint).abs();

    if (axis == BoundBox::Axis::X)
        return extent.x;

    if (axis == BoundBox::Axis::Y)
        return extent.y;

    if (axis == BoundBox::Axis::Z)
        return extent.z;

    return 0;
}

bool BoundBox::isOverlapped(const BoundBox &that) const
{
    float tMinDummy, tMaxDummy;

    bool bX = Common::getOverlap(minPoint.x, maxPoint.x,
                                 that.minPoint.x, that.maxPoint.x,
                                 tMinDummy, tMaxDummy);

    bool bY = Common::getOverlap(minPoint.y, maxPoint.y,
                                 that.minPoint.y, that.maxPoint.y,
                                 tMinDummy, tMaxDummy);

    bool bZ = Common::getOverlap(minPoint.z, maxPoint.z,
                                 that.minPoint.z, that.maxPoint.z,
                                 tMinDummy, tMaxDummy);
    return bX && bY && bZ;
}

void BoundBox::split(BoundBox::Axis axis, BoundBox &outBox1, BoundBox &outBox2) const
{
    BoundBox b1, b2;
    Vector3 minP1, minP2, maxP1, maxP2;
    Vector3 e = (maxPoint - minPoint).abs() / 2;//extent / 2
    Vector3 d;

    //refactor later...
    if(axis == BoundBox::Axis::X)
    {
        d = Vector3(e.x, 0, 0);

        minP1 = minPoint;
        maxP1 = maxPoint - d;
        minP2 = minPoint + d;
        maxP2 = maxPoint;
    }
    else if(axis == BoundBox::Axis::Y)
    {
        d = Vector3(0, e.y, 0);

        minP1 = minPoint;
        maxP1 = maxPoint - d;
        minP2 = minPoint + d;
        maxP2 = maxPoint;
    }
    else
    {
        d = Vector3(0, 0, e.z);

        minP1 = minPoint;
        maxP1 = maxPoint - d;
        minP2 = minPoint + d;
        maxP2 = maxPoint;
    }

    outBox1.reset();
    outBox1.update(minP1);
    outBox1.update(maxP1);

    outBox2.reset();
    outBox2.update(minP2);
    outBox2.update(maxP2);
}

void BoundBox::update(const Vector3 &p)
{
    minPoint = minPoint.min_component_wise(p);
    maxPoint = maxPoint.max_component_wise(p);
}

void BoundBox::update(const BoundBox &b)
{
    this->update(b.minPoint);
    this->update(b.maxPoint);
}

void BoundBox::set(const Vector3 &p1, const Vector3 &p2)
{
    float x_min = std::min(p1.x, p2.x);
    float y_min = std::min(p1.y, p2.y);
    float z_min = std::min(p1.z, p2.z);

    float x_max = std::max(p1.x, p2.x);
    float y_max = std::max(p1.y, p2.y);
    float z_max = std::max(p1.z, p2.z);

    minPoint = Vector3(x_min, y_min, z_min);
    maxPoint = Vector3(x_max, y_max, z_max);
}

bool BoundBox::isInBox(const Vector3 &point) const
{
    bool bX = Common::is_in_range(point.x, minPoint.x, maxPoint.x, true, true);
    bool bY = Common::is_in_range(point.y, minPoint.y, maxPoint.y, true, true);
    bool bZ = Common::is_in_range(point.z, minPoint.z, maxPoint.z, true, true);

    bool isIn = bX && bY && bZ;

    // if(isIn)
    // {
    //     std::cout << "in boundBox" <<std::endl;
    //     std::cout << *this << std::endl;
    // }

    return isIn;
}

bool BoundBox::hit(const Ray &ray, float &t) const
{
    float tMin = Common::FLOAT_POSITIVE_INFINITY;
    float tMax = Common::FLOAT_NEGETIVE_INFINITY;

    Vector3 vecToMin = minPoint - ray.origin;
    Vector3 vecToMax = maxPoint - ray.origin;

    Vector3 resultToMin = vecToMin.div_component_wise(ray.dir);
    Vector3 resultToMax = vecToMax.div_component_wise(ray.dir);

    float tMinXY = Common::FLOAT_POSITIVE_INFINITY;
    float tMaxXY = Common::FLOAT_NEGETIVE_INFINITY;
    bool isXYOverlap = Common::getOverlap(resultToMin.x, resultToMax.x,
                                          resultToMin.y, resultToMax.y,
                                          tMinXY, tMaxXY);
    if(!isXYOverlap)
        return false;

    float tMinXYZ = Common::FLOAT_POSITIVE_INFINITY;
    float tMaxXYZ = Common::FLOAT_NEGETIVE_INFINITY;
    bool isZOverlap = Common::getOverlap(tMinXY, tMaxXY,
                                         resultToMin.z, resultToMax.z,
                                         tMinXYZ, tMaxXYZ);
    if (!isZOverlap)
        return false;

    tMin = tMinXYZ;
    tMax = tMaxXYZ;

    if(tMaxXYZ < 0)
        return false;
    if(tMin >= 0)
        t = tMin;

    t = tMaxXYZ;

    // std::cout << "hit : ( " << tMin << ", " << tMax << " )" << std::endl;

    return true;
}

BoundBox::Axis BoundBox::getMainAxis() const
{
    Vector3 extent = (maxPoint - minPoint).abs();

    float x = extent.x;
    float y = extent.y;
    float z = extent.z;

    if (x > y)
    {
        if (x > z)
            return BoundBox::Axis::X;
        else
            return BoundBox::Axis::Z;
    }
    else
    {
        if (y > z)
            return BoundBox::Axis::Y;
        else
            return BoundBox::Axis::Z;
    }
}

std::ostream &operator<<(std::ostream &os, const BoundBox &boundBox)
{
    os << "---------boundBox-------" << std::endl;
    os << "min: " << boundBox.minPoint << std::endl;
    os << "max: " << boundBox.maxPoint << std::endl;
    os << "end------boundBox-------" << std::endl;

    return os;
}