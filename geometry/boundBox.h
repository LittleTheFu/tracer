#ifndef _BOUND_BOX_H_
#define _BOUND_BOX_H_

#include "axisDef.h"
#include "ray.h"
#include "vector.h"

class BoundBox
{
public:
    BoundBox();
    BoundBox(const Vector3 &p1, const Vector3 &p2);

    void reset();

    Vector3 getCenter() const;
    float getExtentByAxis(Axis axis) const;
    Vector3 getExtend() const;

    float surfaceArea() const;
    float getMaxFaceArea() const;
    float volume() const;

    bool is2dOr3d() const;

    BoundBox createSubBox(Axis axis, float startPercent, float endPercent) const;

    bool isOverlapped(const BoundBox &that) const;
    void split(Axis axis, float percent, BoundBox &outBox1, BoundBox &outBox2) const;
    void update(const Vector3 &p);
    void update(const BoundBox &b);
    
    bool isInBox(const Vector3 &point) const;
    bool hit(const Ray &ray, float &t) const;
    bool hasInfiniteComponent() const;

    BoundBox &operator*=(float m);
    bool operator==(const BoundBox &that) const; 

    Axis getMainAxis() const;

    friend std::ostream &operator<<(std::ostream &os, const BoundBox &boundBox);

private:
    //use update function only!!!
    void set(const Vector3 &p1, const Vector3 &p2);

public:
    Vector3 minPoint;
    Vector3 maxPoint;
};

#endif