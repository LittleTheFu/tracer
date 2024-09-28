#include "mesh.h"
#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags

Mesh::Mesh(const std::string fileName)
{
    std::cout << "starting importer..." << std::endl;
    Assimp::Importer importer;
    std::cout << "starting importer...1" << std::endl;

    const aiScene *scene = importer.ReadFile(fileName.c_str(), 0);
    int faceNUM = scene->mMeshes[0]->mNumFaces;
    std::cout << "face num : " << faceNUM << std::endl;
    for(int i = 0; i < faceNUM; i++)
    {
        std::cout << i;
        aiFace face = scene->mMeshes[0]->mFaces[i];
        for(int j = 0; j < face.mNumIndices; j++)
        {
            std::cout << " " << face.mIndices[j] << ",";
        }
        std::cout << std::endl;
        for(int k = 0; k < face.mNumIndices; k++)
        {
            float x = scene->mMeshes[0]->mVertices[face.mIndices[k]].x;
            float y = scene->mMeshes[0]->mVertices[face.mIndices[k]].y;
            float z = scene->mMeshes[0]->mVertices[face.mIndices[k]].z;
            std::cout << "[" << x << "," << y << "," << z << "]";
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    //   // If the import failed, report it
    //   if (nullptr == scene) {
    //     DoTheErrorLogging( importer.GetErrorString());
    //     return false;
    //   }
}

bool Mesh::hit(const Ray &ray, HitRecord &record, Light *pLight) const
{
    return false;
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