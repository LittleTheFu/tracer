#ifndef _MESH_H_
#define _MESH_H_

#include <memory>
#include <vector>

#include "geometry.h"
#include "material.h"
#include "objectpool.h"
#include "tri.h"

class Mesh : public Geometry
{
public:
    Mesh(const std::string fileName, const Vector3 pos, float scale, std::shared_ptr<Material> pMtrl);

    virtual bool hit(const Ray &ray, HitRecord &record) const override;

public:
    void addToPool(std::shared_ptr<ObjectPool> pool);
private:
    virtual Vector3 dpdu(const Vector3 &point) const override;
    virtual Vector3 dpdv(const Vector3 &point) const override;

    virtual float u(const Vector3 &point) const override;
    virtual float v(const Vector3 &point) const override;

public:
    std::vector<std::shared_ptr<Tri>> m_tris;
};

#endif