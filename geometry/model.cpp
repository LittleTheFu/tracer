#include "model.h"

#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include <assert.h>
#include "mesh.h"

Model::Model(const std::string fileName, const Vector3 pos, float scale)
{
    assert(scale > 0);

    std::cout << "starting importer..." << std::endl;
    Assimp::Importer importer;
    std::cout << "starting importer...1" << std::endl;

    const aiScene *scene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    bool hasMaterial = scene->HasMaterials();

    for (int i = 0; i < scene->mNumMeshes; i++)
    {
        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
        mesh->create(scene->mMeshes[i], scene->mMaterials, scale, pos);
        meshes.push_back(mesh);
    }
}