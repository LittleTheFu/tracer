#include <cassert>

#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include "mesh.h"

Mesh::Mesh(const std::string fileName, const Vector3 pos, float scale, std::shared_ptr<Material> pMtrl)
{
    assert(scale > 0);

    std::cout << "starting importer..." << std::endl;
    Assimp::Importer importer;
    std::cout << "starting importer...1" << std::endl;

    const aiScene *scene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    int faceNUM = scene->mMeshes[0]->mNumFaces;
    std::cout << "face num : " << faceNUM << std::endl;
    for(int i = 0; i < faceNUM; i++)
    {
        aiFace face = scene->mMeshes[0]->mFaces[i];
        assert(face.mNumIndices == 3);

        TriVertex va = createTriVertex(scene->mMeshes[0], face.mIndices[0], scale);
        TriVertex vb = createTriVertex(scene->mMeshes[0], face.mIndices[1], scale);
        TriVertex vc = createTriVertex(scene->mMeshes[0], face.mIndices[2], scale);

        // va.setUV(u_a, v_a);
        // vb.setUV(u_b, v_b);
        // vc.setUV(u_c, v_c);

        auto tri = std::make_shared<Tri>(va, vb, vc, pos, pMtrl);

        m_tris.push_back(tri);
    }
}

TriVertex Mesh::createTriVertex(const aiMesh* mesh, unsigned int index, float scale) const {
    float x = mesh->mVertices[index].x;
    float y = mesh->mVertices[index].y;
    float z = mesh->mVertices[index].z;
    float n_x = mesh->mNormals[index].x;
    float n_y = mesh->mNormals[index].y;
    float n_z = mesh->mNormals[index].z;
    // float u = mesh->mTextureCoords[0][index].x;
    // float v = mesh->mTextureCoords[0][index].y;

    return TriVertex(x * scale, y * scale, z * scale, n_x, n_y, n_z);
}

bool Mesh::hit(const Ray &ray, HitRecord &record) const
{
    return false;
}

void Mesh::addToPool(std::shared_ptr<ObjectPool> pool)
{
    for(auto it = m_tris.begin(); it != m_tris.end(); it++)
    {
        pool->add(*it);
    }
}

Vector3 Mesh::dpdu(const Vector3 &point) const
{
    return Vector3::ZERO;
}

Vector3 Mesh::dpdv(const Vector3 &point) const
{
    return Vector3::ZERO;
}

float Mesh::u(const Vector3 &point) const
{
    return 0;
}

float Mesh::v(const Vector3 &point) const
{
    return 0;
}
