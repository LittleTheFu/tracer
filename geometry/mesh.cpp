#include <cassert>

#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include "mesh.h"
#include "geometryPrimitive.h"
#include "materialLambertian.h"
#include "materialManager.h"
#include <materialPBR.h>

Mesh::Mesh(const std::string fileName,
           const Vector3 pos,
           float scale)
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
    if(hasMaterial)
    {
        aiMaterial *mat = scene->mMaterials[0];
        assert(mat);

        aiColor3D color;
        mat->Get(AI_MATKEY_BASE_COLOR, color);
        Color albedo(color.r, color.g, color.b);
        albedo.clamp();
        std::cout << "albedo : " << albedo << std::endl;
        
        float roughness = 0.0f;
        mat->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughness);
        std::cout << "roughness : " << roughness << std::endl;

        float metallic = 0.0f;
        mat->Get(AI_MATKEY_METALLIC_FACTOR, metallic);
        std::cout << "metallic : " << metallic << std::endl;

        // float ior = 1.5f;
        // mat->Get(AI_MATKEY_REFRACTI, ior);
        // std::cout << "ior : " << ior << std::endl;
        
        std::shared_ptr<MaterialPBR> material = std::make_shared<MaterialPBR>(albedo, roughness, metallic);
        materialId_ = MaterialManager::getInstance().addMaterial(material);
    }

    for (int i = 0; i < scene->mNumMeshes; i++)
    {

        int faceNUM = scene->mMeshes[i]->mNumFaces;
        std::cout << "face num : " << faceNUM << std::endl;
        for (int j = 0; j < faceNUM; j++)
        {
            aiFace face = scene->mMeshes[i]->mFaces[j];
            assert(face.mNumIndices == 3);

            TriVertex va = createTriVertex(scene->mMeshes[0], face.mIndices[0], scale);
            TriVertex vb = createTriVertex(scene->mMeshes[0], face.mIndices[1], scale);
            TriVertex vc = createTriVertex(scene->mMeshes[0], face.mIndices[2], scale);

            // va.setUV(u_a, v_a);
            // vb.setUV(u_b, v_b);
            // vc.setUV(u_c, v_c);

            auto tri = std::make_shared<Tri>(va, vb, vc, pos);

            m_tris.push_back(tri);
        }
    }
}

TriVertex Mesh::createTriVertex(const aiMesh *mesh, unsigned int index, float scale) const
{
    float x = mesh->mVertices[index].x;
    float y = mesh->mVertices[index].y;
    float z = mesh->mVertices[index].z;
    float n_x = mesh->mNormals[index].x;
    float n_y = mesh->mNormals[index].y;
    float n_z = mesh->mNormals[index].z;
    float u = mesh->mTextureCoords[0][index].x;
    float v = mesh->mTextureCoords[0][index].y;

    TriVertex tri(x * scale, y * scale, z * scale, n_x, n_y, n_z);
    tri.setUV(u, v);

    return tri;
}

bool Mesh::hit(const Ray &ray, Interaction &interaction) const
{
    return false;
}

void Mesh::addToPool(std::shared_ptr<ObjectPool> pool, std::shared_ptr<Material> material)
{
    for (auto it = m_tris.begin(); it != m_tris.end(); it++)
    {
        std::shared_ptr<GeometryPrimitive> primitive = std::make_shared<GeometryPrimitive>(*it, material);
        pool->addPrimitive(primitive);
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
