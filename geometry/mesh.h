#ifndef _MESH_H_
#define _MESH_H_

#include <memory>
#include <vector>

#include <assimp/mesh.h>

#include "geometry.h"
#include "objectpool.h"
#include "tri.h"
#include "material.h"
#include <assimp/material.h>

class Mesh : public Geometry
{
public:
    Mesh();

    void create(const aiMesh *mesh, aiMaterial **materials, float scale, const Vector3 pos);

    // Mesh(const std::string fileName,
    //      const Vector3 pos,
    //      float scale);

    virtual bool hit(const Ray &ray, Interaction &interaction) const override;

public:
    void addToPool(std::shared_ptr<ObjectPool> pool,
                   std::shared_ptr<Material> material,
                   std::shared_ptr<MediumBoundary> mediumBoundary = nullptr);

    // we don't calculate things related to uv in mesh but in tri
private:
    virtual Vector3 dpdu(const Vector3 &point) const override;
    virtual Vector3 dpdv(const Vector3 &point) const override;

    virtual float u(const Vector3 &point) const override;
    virtual float v(const Vector3 &point) const override;

private:
    TriVertex createTriVertex(const aiMesh* mesh, unsigned int index, float scale) const;


public:
    std::vector<std::shared_ptr<Tri>> m_tris;

//temporary solution
//and assuming there is at most 1 materail can be loaded from the file
private:
    int materialId_ = -1;//WARNING: magic number---quick and dirty,I will come back here later
public:
    int getMaterialId() const { return materialId_; }
};

#endif