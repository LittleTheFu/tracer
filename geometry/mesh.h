#ifndef _MESH_H_
#define _MESH_H_

#include "geometry.h"
#include "tri.h"
#include <vector>
#include "material.h"
#include "objectpool.h"

class Mesh : public Geometry
{
public:
    Mesh(const std::string fileName, Material *pMtrl);

    virtual bool hit(const Ray &ray, HitRecord &record, Light *pLight) const override;

public:
    void addToPool(ObjectPool *pool);
private:
    virtual Vector3 dpdu(const Vector3 &point) const override;
    virtual Vector3 dpdv(const Vector3 &point) const override;

    virtual float u(const Vector3 &point) const override;
    virtual float v(const Vector3 &point) const override;

public:
    std::vector<Tri*> m_tris;
};

#endif