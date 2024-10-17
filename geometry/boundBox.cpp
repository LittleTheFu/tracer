#include "boundBox.h"
#include <algorithm>
#include <cassert>

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

    // assert(minPoint.less_or_equal_component_wise(maxPoint));
}

Vector3 BoundBox::getCenter() const
{
    Vector3 center = ( minPoint + maxPoint ) / 2;

    return center;
}

float BoundBox::getExtentByAxis(Common::Axis axis) const
{
    Vector3 extent = getExtend();

    if (axis == Common::Axis::X)
        return extent.x;

    if (axis == Common::Axis::Y)
        return extent.y;

    if (axis == Common::Axis::Z)
        return extent.z;

    return 0;
}

Vector3 BoundBox::getExtend() const
{
    Vector3 extent = (maxPoint - minPoint).abs();

    return extent;
}

float BoundBox::surfaceArea() const
{
    assert(!hasInfiniteComponent());
    Vector3 e = getExtend();
    float area = 2 * ( e.x * e.y + e.y * e.z + e.z * e.x );

    return area;
}

BoundBox BoundBox::createSubBox(Common::Axis axis, float startPercent, float endPercent) const
{
    assert(startPercent < endPercent);
    assert(Common::is_in_range(startPercent, 0, 1, true, true));
    assert(Common::is_in_range(endPercent, 0, 1, true, true));

    Vector3 e = maxPoint - minPoint;
    Vector3 min = minPoint;
    Vector3 max = maxPoint;

    if(axis == Common::Axis::X)
    {
        min.x = min.x + e.x * startPercent;
        max.x = min.x + e.x * endPercent;
    }
    else if(axis == Common::Axis::Y)
    {
        min.y = min.y + e.y * startPercent;
        max.y = min.y + e.y * endPercent;
    }
    else
    {
        min.z = min.z + e.z * startPercent;
        max.z = min.z + e.z * endPercent;
    }

    BoundBox box;
    box.update(min);
    box.update(max);

    return box;
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

void BoundBox::split(Common::Axis axis, float percent, BoundBox &outBox1, BoundBox &outBox2) const
{
    assert(!hasInfiniteComponent());
    assert(Common::is_in_range(percent, 0, 1, true, true));

    Vector3 minP1 = minPoint;
    Vector3 maxP1 = maxPoint;
    Vector3 minP2 = minPoint;
    Vector3 maxP2 = maxPoint;

    Vector3 e = (maxPoint - minPoint) * percent;

    if(axis == Common::Axis::X)
    {
        maxP1.x = minPoint.x + e.x;
        minP2.x = minPoint.x + e.x;
    }
    else if(axis == Common::Axis::Y)
    {
        maxP1.y = minPoint.y + e.y;
        minP2.y = minPoint.y + e.y;
    }
    else
    {
        maxP1.z = minPoint.z + e.z;
        minP2.z = minPoint.z + e.z;
    }

    outBox1.reset();
    outBox1.update(minP1);
    outBox1.update(maxP1);
    // assert(!outBox1.hasInfiniteComponent());

    outBox2.reset();
    outBox2.update(minP2);
    outBox2.update(maxP2);
    // assert(!outBox2.hasInfiniteComponent());

    // BoundBox bb1 = outBox1;
    // BoundBox bb2 = outBox2;
    // bb1.update(bb2);
    // assert(this->operator==(bb1));
}

void BoundBox::update(const Vector3 &p)
{
    minPoint = minPoint.min_component_wise(p);
    maxPoint = maxPoint.max_component_wise(p);

    assert(!hasInfiniteComponent());
    // assert(minPoint.less_or_equal_component_wise(maxPoint));
}

void BoundBox::update(const BoundBox &b)
{
    this->update(b.minPoint);
    this->update(b.maxPoint);

    assert(!hasInfiniteComponent());
}

void BoundBox::set(const Vector3 &p1, const Vector3 &p2)
{
    minPoint = p1.min_component_wise(p2);
    maxPoint = p1.max_component_wise(p2);

    assert(!hasInfiniteComponent());
    // assert(minPoint.less_or_equal_component_wise(maxPoint));
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
    // assert(!hasInfiniteComponent());
    if(ray.dir == Vector3::ZERO)
        return false;
        
    float tMin = Common::FLOAT_POSITIVE_INFINITY;
    float tMax = Common::FLOAT_NEGETIVE_INFINITY;

    Vector3 vecToMin = minPoint - ray.origin;
    Vector3 vecToMax = maxPoint - ray.origin;
   
    Vector3 resultToMin = vecToMin.div_component_wise(ray.dir);
    Vector3 resultToMax = vecToMax.div_component_wise(ray.dir);

    Vector3 localMin = resultToMin.min_component_wise(resultToMax);
    Vector3 localMax = resultToMin.max_component_wise(resultToMax);

    // assert(localMin.less_or_equal_component_wise(localMax));

    float tMinXY = Common::FLOAT_POSITIVE_INFINITY;
    float tMaxXY = Common::FLOAT_NEGETIVE_INFINITY;
    bool isXYOverlap = Common::getOverlap(localMin.x, localMax.x,
                                          localMin.y, localMax.y,
                                          tMinXY, tMaxXY);
    if(!isXYOverlap)
        return false;

    float tMinXYZ = Common::FLOAT_POSITIVE_INFINITY;
    float tMaxXYZ = Common::FLOAT_NEGETIVE_INFINITY;
    bool isZOverlap = Common::getOverlap(tMinXY, tMaxXY,
                                         localMin.z, localMax.z,
                                         tMinXYZ, tMaxXYZ);
    if (!isZOverlap)
        return false;

    assert(tMinXYZ <= tMaxXYZ);

    if(tMaxXYZ < 0)
        return false;

    if(tMinXYZ >= 0)
    {
        t = tMinXYZ;
        return true;
    }
    else
    {
        t = tMaxXYZ;
    }

    assert(t >= 0);
    // std::cout << "hit : ( " << tMin << ", " << tMax << " )" << std::endl;

    return true;
}

bool BoundBox::hasInfiniteComponent() const
{
    if(minPoint.x == Common::FLOAT_NEGETIVE_INFINITY)   return true;
    if(minPoint.x == Common::FLOAT_POSITIVE_INFINITY)   return true;

    if(minPoint.y == Common::FLOAT_NEGETIVE_INFINITY)   return true;
    if(minPoint.y == Common::FLOAT_POSITIVE_INFINITY)   return true;

    if(minPoint.z == Common::FLOAT_NEGETIVE_INFINITY)   return true;
    if(minPoint.z == Common::FLOAT_POSITIVE_INFINITY)   return true;

    if(maxPoint.x == Common::FLOAT_NEGETIVE_INFINITY)   return true;
    if(maxPoint.x == Common::FLOAT_POSITIVE_INFINITY)   return true;

    if(maxPoint.y == Common::FLOAT_NEGETIVE_INFINITY)   return true;
    if(maxPoint.y == Common::FLOAT_POSITIVE_INFINITY)   return true;

    if(maxPoint.z == Common::FLOAT_NEGETIVE_INFINITY)   return true;
    if(maxPoint.z == Common::FLOAT_POSITIVE_INFINITY)   return true;

    return false;
}

BoundBox &BoundBox::operator*=(float m)
{
    Vector3 ext = (maxPoint - minPoint) * (m - 1);
    Vector3 min = minPoint - ext;
    Vector3 max= maxPoint + ext;

    update(min);
    update(max);

    return *this;
}

bool BoundBox::operator==(const BoundBox &that) const
{
    bool bMinEq = ( minPoint == that.minPoint );
    bool bMaxEq = ( maxPoint == that.maxPoint );

    return bMinEq && bMaxEq;
}

Common::Axis BoundBox::getMainAxis() const
{
    Vector3 extent = getExtend();

    float x = extent.x;
    float y = extent.y;
    float z = extent.z;

    if (x > y)
    {
        if (x > z)
            return Common::Axis::X;
        else
            return Common::Axis::Z;
    }
    else
    {
        if (y > z)
            return Common::Axis::Y;
        else
            return Common::Axis::Z;
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