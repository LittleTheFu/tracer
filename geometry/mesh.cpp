#include <cassert>

#include <assimp/Importer.hpp>  // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include "mesh.h"
#include "geometryPrimitive.h"
#include "materialLambertian.h"
#include "materialManager.h"
#include "materialPBR.h"
#include "resourceDef.h"
#include <emittingMaterial.h>
#include <materialMirror.h>

Mesh::Mesh()
{
}

void Mesh::create(const aiMesh *mesh, aiMaterial **materials, float scale, const Vector3 pos)
{
    int faceNUM = mesh->mNumFaces;
    std::cout << "face num : " << faceNUM << std::endl;
    for (int j = 0; j < faceNUM; j++)
    {
        aiFace face = mesh->mFaces[j];
        assert(face.mNumIndices == 3);

        TriVertex va = createTriVertex(mesh, face.mIndices[0], scale);
        TriVertex vb = createTriVertex(mesh, face.mIndices[1], scale);
        TriVertex vc = createTriVertex(mesh, face.mIndices[2], scale);

        // va.setUV(u_a, v_a);
        // vb.setUV(u_b, v_b);
        // vc.setUV(u_c, v_c);

        auto tri = std::make_shared<Tri>(va, vb, vc, pos);

        m_tris.push_back(tri);
    }

    if (mesh->mMaterialIndex >= 0)
    {
        const aiMaterial *mat = materials[mesh->mMaterialIndex];

        aiColor3D emissiveColor(0.0f, 0.0f, 0.0f);
        mat->Get(AI_MATKEY_COLOR_EMISSIVE, emissiveColor);
        if (emissiveColor.r > 0.0f || emissiveColor.g > 0.0f || emissiveColor.b > 0.0f)
        {
            std::shared_ptr<EmittingMaterial> material = std::make_shared<EmittingMaterial>();
            material->setEmittedRadiance(Color(emissiveColor.r, emissiveColor.g, emissiveColor.b));
            materialId_ = MaterialManager::getInstance().addMaterial(material);

            return ;
        }
        
        aiColor3D color;
        // mat->Get(AI_MATKEY_BASE_COLOR, color);
        mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        Color albedo(color.r, color.g, color.b);
        albedo.clamp();
        std::cout << "albedo : " << albedo << std::endl;

        float roughness = 0.0f;
        mat->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughness);
        std::cout << "roughness : " << roughness << std::endl;

        float metallic = 0.0f;
        mat->Get(AI_MATKEY_METALLIC_FACTOR, metallic);
        std::cout << "metallic : " << metallic << std::endl;

        //should be relaced this with texture manager,I will do it later...
        if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString str;
            mat->GetTexture(aiTextureType_DIFFUSE, 0, &str);
            std::string texturePath = str.C_Str();
            std::replace(texturePath.begin(), texturePath.end(), '\\', '/');
            std::cout << "texture path : " << texturePath << std::endl;

            std::unique_ptr<Texture> texture = std::make_unique<ImageTexture>(ResourceDef::RES_FOLDER + texturePath);
            assert(texture);

            std::shared_ptr<MaterialPBR> material = std::make_shared<MaterialPBR>(albedo, roughness, metallic, std::move(texture));
            // std::shared_ptr<MaterialMirror> material = std::make_shared<MaterialMirror>();
            materialId_ = MaterialManager::getInstance().addMaterial(material);
        }
        else //dupliacated code should be extracted here, I will come here later...
        {
            std::shared_ptr<MaterialPBR> material = std::make_shared<MaterialPBR>(albedo, roughness, metallic, nullptr);
            // std::shared_ptr<MaterialMirror> material = std::make_shared<MaterialMirror>();
            materialId_ = MaterialManager::getInstance().addMaterial(material);
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

void Mesh::addToPool(std::shared_ptr<ObjectPool> pool, 
    std::shared_ptr<Material> material, 
    std::shared_ptr<MediumBoundary> mediumBoundary)
{
    for (auto it = m_tris.begin(); it != m_tris.end(); it++)
    {
        std::shared_ptr<GeometryPrimitive> primitive = std::make_shared<GeometryPrimitive>(*it, material, mediumBoundary);
        pool->addPrimitive(primitive);

        //quick but dirty
        if(dynamic_cast<EmittingMaterial*>(material.get()))
        {
            std::shared_ptr<AreaLight> light = std::make_shared<AreaLight>(primitive);
            pool->addLight(light);
        }
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
