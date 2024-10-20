#ifndef _C_PLANE_H_
#define _C_PLANE_H_

#include "geometry.h"
#include "material.h"

class Plane : public Geometry
{
public:
    Plane(const Vector3 &rotate, const Vector3 &position, float length, const Material *pMtrl);
    virtual bool hit(const Ray &ray, HitRecord &record) const override;

    virtual Vector3 getCentroid() const;
    virtual float surfaceArea() const override;
    virtual void buildBoundBox() override;

public:
    float half_length;

private:
    virtual Vector3 dpdu(const Vector3 &point) const override;
    virtual Vector3 dpdv(const Vector3 &point) const override;

    virtual float u(const Vector3 &point) const override;
    virtual float v(const Vector3 &point) const override;

    Vector3 getLocalNormal(bool reverse) const;
    bool isLocalIn(const Vector3 &p) const;

    int m_uvCellSize;

private:
    void HandleMaterial(const Ray &newRay, HitRecord &record) const;
};

#endif