#ifndef _BOUND_BOX_H_
#define _BOUND_BOX_H_

#include "vector.h"
#include <ray.h>

class BoundBox
{
public:
    enum class Axis
    {
        X = 0,
        Y,
        Z,
    };

public:
    BoundBox();
    BoundBox(const Vector3 &p1, const Vector3 &p2);

    void reset();

    Vector3 getCenter() const;
    float getExtent(BoundBox::Axis axis) const;

    bool isOverlapped(const BoundBox &that) const;
    void split(BoundBox::Axis axis, BoundBox &outBox1, BoundBox &outBox2) const;
    void update(const Vector3 &p);
    void update(const BoundBox &b);
    
    bool isInBox(const Vector3 &point) const;
    bool hit(const Ray &ray, float &t) const;

    BoundBox::Axis getMainAxis() const;

    friend std::ostream &operator<<(std::ostream &os, const BoundBox &boundBox);

private:
    //use update function only!!!
    void set(const Vector3 &p1, const Vector3 &p2);

public:
    Vector3 minPoint;
    Vector3 maxPoint;
};

#endif