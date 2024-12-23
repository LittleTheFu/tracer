#ifndef _SCENE_BUILDER_H_
#define _SCENE_BUILDER_H_

#include "diffuseMaterial.h"
#include "mirrorMaterial.h"
#include "glassMaterial.h"
#include "dielectricMaterial.h"
#include "objectpool.h"
#include "materialDef.h"
#include <memory>

class SceneBuilder
{
public:
    void init(std::shared_ptr<ObjectPool> pool);
    virtual void build() = 0;

protected:
    void buildRoom();
    void buildMeshRoom();
    void buildLight(const Vector3& pos, float r);

    void buildSceneWithDefaultConfig();

    void buildGlassBall(const Vector3& pos, float r);
    void buildMirrorBall(const Vector3& pos, float r);
    void buildMixBall(const Vector3& pos, float r);

    void buildMeasuredWhiteBall(const Vector3& pos, float r);
    void buildMeasuredGreenBall(const Vector3& pos, float r);
    void buildMeasuredMetalBall(const Vector3& pos, float r);
    void buildMeasuredMintBall(const Vector3& pos, float r);
    void buildMeasuredGreenPvcBall(const Vector3& pos, float r);
    void buildMeasuredBrushedAluminiumBall(const Vector3& pos, float r);
    void buildMeasuredTarkinTunicBall(const Vector3& pos, float r);
    void buildMeasuredSariSilkBall(const Vector3& pos, float r);

    void buildVolumeBall(const Vector3& pos, float r);

    void buildRedBall(const Vector3& pos, float r);
    void buildAquaBall(const Vector3& pos, float r);

    void buildConductorBall(const Vector3& pos, float r);

    void buildBunny(const Vector3& pos, float scale, const std::string& res, MATERIAL_TYPE materialType);

    void buildRedTri(const Vector3& pos);
    void buildGreenTri(const Vector3& pos);

    void buildGlassTri(const Vector3& pos);

protected:
    std::shared_ptr<ObjectPool> m_pObjectPool;
};

#endif