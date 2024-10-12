#include "mesh.h"
#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include <cassert>

Mesh::Mesh(const std::string fileName, const Vector3 pos, float scale, Material *pMtrl)
{
    assert(scale > 0);

    std::cout << "starting importer..." << std::endl;
    Assimp::Importer importer;
    std::cout << "starting importer...1" << std::endl;

    const aiScene *scene = importer.ReadFile(fileName.c_str(), 0);
    int faceNUM = scene->mMeshes[0]->mNumFaces;
    std::cout << "face num : " << faceNUM << std::endl;
    for(int i = 0; i < faceNUM; i++)
    {
        aiFace face = scene->mMeshes[0]->mFaces[i];
        assert(face.mNumIndices == 3);

        float x_a = scene->mMeshes[0]->mVertices[face.mIndices[0]].x;
        float y_a = scene->mMeshes[0]->mVertices[face.mIndices[0]].y;
        float z_a = scene->mMeshes[0]->mVertices[face.mIndices[0]].z;
        // float n_x_a = scene->mMeshes[0]->mNormals[face.mIndices[0]].x;
        // float n_y_a = scene->mMeshes[0]->mNormals[face.mIndices[0]].y;
        // float n_z_a = scene->mMeshes[0]->mNormals[face.mIndices[0]].z;

        float x_b = scene->mMeshes[0]->mVertices[face.mIndices[1]].x;
        float y_b = scene->mMeshes[0]->mVertices[face.mIndices[1]].y;
        float z_b = scene->mMeshes[0]->mVertices[face.mIndices[1]].z;
        // float n_x_b = scene->mMeshes[0]->mNormals[face.mIndices[1]].x;
        // float n_y_b = scene->mMeshes[0]->mNormals[face.mIndices[1]].y;
        // float n_z_b = scene->mMeshes[0]->mNormals[face.mIndices[1]].z;

        float x_c = scene->mMeshes[0]->mVertices[face.mIndices[2]].x;
        float y_c = scene->mMeshes[0]->mVertices[face.mIndices[2]].y;
        float z_c = scene->mMeshes[0]->mVertices[face.mIndices[2]].z;
        // float n_x_c = scene->mMeshes[0]->mNormals[face.mIndices[2]].x;
        // float n_y_c = scene->mMeshes[0]->mNormals[face.mIndices[2]].y;
        // float n_z_c = scene->mMeshes[0]->mNormals[face.mIndices[2]].z;

        // TriVertex va(x_a * scale, y_a * scale, z_a * scale, n_x_a, n_y_a, n_z_a);
        // TriVertex vb(x_b * scale, y_b * scale, z_b * scale, n_x_b, n_y_b, n_z_b);
        // TriVertex vc(x_c * scale, y_c * scale, z_c * scale, n_x_c, n_y_c, n_z_c);

        TriVertex va(x_a * scale, y_a * scale, z_a * scale);
        TriVertex vb(x_b * scale, y_b * scale, z_b * scale);
        TriVertex vc(x_c * scale, y_c * scale, z_c * scale);

        Tri *tri = new Tri(va, vb, vc, pos, pMtrl);

        m_tris.push_back(tri);
    }
}

bool Mesh::hit(const Ray &ray, HitRecord &record) const
{
    return false;
}

void Mesh::addToPool(ObjectPool *pool)
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