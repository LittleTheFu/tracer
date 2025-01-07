#ifndef _C_PLANE_H_
#define _C_PLANE_H_

#include <memory>

#include "geometry.h"
#include "material.h"

class Plane : public Geometry
{
public:
    Plane(const Vector3 &rotate, const Vector3 &position, float length, std::shared_ptr<Material> pMtrl);
    virtual bool hit(const Ray &ray, HitRecord &record) const override;

    virtual Vector3 getCentroid() const override;
    virtual float surfaceArea() const override;
    virtual void buildBoundBox() override;

    virtual bool testHit(const Ray &localRay, float &t) const override;

public:
    float half_length;

private:
    virtual Vector3 dpdu(const Vector3 &point) const override;
    virtual Vector3 dpdv(const Vector3 &point) const override;

    virtual float u(const Vector3 &point) const override;
    virtual float v(const Vector3 &point) const override;

    bool isLocalIn(const Vector3 &p) const;

    int m_uvCellSize;

private:
    void HandleMaterial(const Ray &newRay, HitRecord &record) const;
};

#endif