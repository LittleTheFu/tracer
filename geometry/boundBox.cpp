#include <algorithm>
#include <cassert>

#include "boundBox.h"
#include "mathConstantDef.h"
#include "mathUtility.h"

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
    float negInf = MathConstant::FLOAT_NEGETIVE_INFINITY;
    float posInf = MathConstant::FLOAT_POSITIVE_INFINITY;

    minPoint = Vector3(posInf, posInf, posInf);
    maxPoint = Vector3(negInf, negInf, negInf);

    // assert(minPoint.less_or_equal_component_wise(maxPoint));
}

Vector3 BoundBox::getCenter() const
{
    Vector3 center = ( minPoint + maxPoint ) / 2;

    return center;
}

float BoundBox::getExtentByAxis(Axis axis) const
{
    Vector3 extent = getExtend();

    if (axis == Axis::X)
        return extent.x;

    if (axis == Axis::Y)
        return extent.y;

    if (axis == Axis::Z)
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

float BoundBox::getMaxFaceArea() const
{
    Vector3 e = getExtend();

    float xy = e.x * e.y;
    float yz = e.y * e.z;
    float zx = e.z * e.x;

    //for clarity
    float max = MathUtility::getMax(xy, yz, zx);

    return max;
}

float BoundBox::volume() const
{
    Vector3 e = getExtend();
    float volume = e.x * e.y * e.z;//for clarity

    return volume;
}

bool BoundBox::is2dOr3d() const
{
    if(volume() > 0.0f)
        return true;

    if(getMaxFaceArea() > 0.0f)
        return true;

    return false;
}

BoundBox BoundBox::createSubBox(Axis axis, float startPercent, float endPercent) const
{
    assert(startPercent < endPercent);
    assert(MathUtility::is_in_range(startPercent, 0, 1, true, true));
    assert(MathUtility::is_in_range(endPercent, 0, 1, true, true));

    Vector3 e = maxPoint - minPoint;
    Vector3 min = minPoint;
    Vector3 max = maxPoint;

    if(axis == Axis::X)
    {
        min.x = min.x + e.x * startPercent;
        max.x = min.x + e.x * endPercent;
    }
    else if(axis == Axis::Y)
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

    bool bX = MathUtility::getOverlap(minPoint.x, maxPoint.x,
                                 that.minPoint.x, that.maxPoint.x,
                                 tMinDummy, tMaxDummy);

    bool bY = MathUtility::getOverlap(minPoint.y, maxPoint.y,
                                 that.minPoint.y, that.maxPoint.y,
                                 tMinDummy, tMaxDummy);

    bool bZ = MathUtility::getOverlap(minPoint.z, maxPoint.z,
                                 that.minPoint.z, that.maxPoint.z,
                                 tMinDummy, tMaxDummy);
    return bX && bY && bZ;
}

void BoundBox::split(Axis axis, float percent, BoundBox &outBox1, BoundBox &outBox2) const
{
    assert(!hasInfiniteComponent());
    assert(MathUtility::is_in_range(percent, 0, 1, true, true));

    Vector3 minP1 = minPoint;
    Vector3 maxP1 = maxPoint;
    Vector3 minP2 = minPoint;
    Vector3 maxP2 = maxPoint;

    Vector3 e = (maxPoint - minPoint) * percent;

    if(axis == Axis::X)
    {
        maxP1.x = minPoint.x + e.x;
        minP2.x = minPoint.x + e.x;
    }
    else if(axis == Axis::Y)
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
    bool bX = MathUtility::is_in_range(point.x, minPoint.x, maxPoint.x, true, true);
    bool bY = MathUtility::is_in_range(point.y, minPoint.y, maxPoint.y, true, true);
    bool bZ = MathUtility::is_in_range(point.z, minPoint.z, maxPoint.z, true, true);

    bool isIn = bX && bY && bZ;

    return isIn;
}

bool BoundBox::hit(const Ray &ray, float &t) const
{
    // assert(!hasInfiniteComponent());
    if(ray.dir == Vector3::ZERO)
        return false;
        
    float tMin = MathConstant::FLOAT_POSITIVE_INFINITY;
    float tMax = MathConstant::FLOAT_NEGETIVE_INFINITY;

    Vector3 vecToMin = minPoint - ray.origin;
    Vector3 vecToMax = maxPoint - ray.origin;
   
    Vector3 resultToMin = vecToMin.div_component_wise(ray.dir);
    Vector3 resultToMax = vecToMax.div_component_wise(ray.dir);

    Vector3 localMin = resultToMin.min_component_wise(resultToMax);
    Vector3 localMax = resultToMin.max_component_wise(resultToMax);

    // assert(localMin.less_or_equal_component_wise(localMax));

    float tMinXY = MathConstant::FLOAT_POSITIVE_INFINITY;
    float tMaxXY = MathConstant::FLOAT_NEGETIVE_INFINITY;
    bool isXYOverlap = MathUtility::getOverlap(localMin.x, localMax.x,
                                          localMin.y, localMax.y,
                                          tMinXY, tMaxXY);
    if(!isXYOverlap)
        return false;

    float tMinXYZ = MathConstant::FLOAT_POSITIVE_INFINITY;
    float tMaxXYZ = MathConstant::FLOAT_NEGETIVE_INFINITY;
    bool isZOverlap = MathUtility::getOverlap(tMinXY, tMaxXY,
                                         localMin.z, localMax.z,
                                         tMinXYZ, tMaxXYZ);
    if (!isZOverlap)
        return false;

    // assert(tMinXYZ <= tMaxXYZ);

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

    if(t >= 0)
    {
        return true;
    }
    //nan needed to be handled,later....
    // assert(t >= 0);
    // std::cout << "hit : ( " << tMin << ", " << tMax << " )" << std::endl;

    return false;
}

bool BoundBox::hasInfiniteComponent() const
{
    if(minPoint.x == MathConstant::FLOAT_NEGETIVE_INFINITY)   return true;
    if(minPoint.x == MathConstant::FLOAT_POSITIVE_INFINITY)   return true;

    if(minPoint.y == MathConstant::FLOAT_NEGETIVE_INFINITY)   return true;
    if(minPoint.y == MathConstant::FLOAT_POSITIVE_INFINITY)   return true;

    if(minPoint.z == MathConstant::FLOAT_NEGETIVE_INFINITY)   return true;
    if(minPoint.z == MathConstant::FLOAT_POSITIVE_INFINITY)   return true;

    if(maxPoint.x == MathConstant::FLOAT_NEGETIVE_INFINITY)   return true;
    if(maxPoint.x == MathConstant::FLOAT_POSITIVE_INFINITY)   return true;

    if(maxPoint.y == MathConstant::FLOAT_NEGETIVE_INFINITY)   return true;
    if(maxPoint.y == MathConstant::FLOAT_POSITIVE_INFINITY)   return true;

    if(maxPoint.z == MathConstant::FLOAT_NEGETIVE_INFINITY)   return true;
    if(maxPoint.z == MathConstant::FLOAT_POSITIVE_INFINITY)   return true;

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

Axis BoundBox::getMainAxis() const
{
    Vector3 extent = getExtend();

    float x = extent.x;
    float y = extent.y;
    float z = extent.z;

    int idx = MathUtility::getMaxIndex(x, y, z);

    if (idx == 0)
        return Axis::X;
    else if (idx == 1)
        return Axis::Y;
    else
        return Axis::Z;
}

std::ostream &operator<<(std::ostream &os, const BoundBox &boundBox)
{
    os << "---------boundBox-------" << std::endl;
    os << "min: " << boundBox.minPoint << std::endl;
    os << "max: " << boundBox.maxPoint << std::endl;
    os << "end------boundBox-------" << std::endl;

    return os;
}