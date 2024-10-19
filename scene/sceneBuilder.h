#ifndef _SCENE_BUILDER_H_
#define _SCENE_BUILDER_H_

#include "lambertianMaterial.h"
#include "mirrorMaterial.h"
#include "glassMaterial.h"
#include "mixMaterial.h"
#include "objectpool.h"

class SceneBuilder
{
public:
    void init(ObjectPool *pool);
    virtual void build() = 0;

protected:
    void buildRoom();
    void buildMeshRoom();
    void buildLight(const Vector3& pos, float r);

    void buildSceneWithDefaultConfig();

    void buildGlassBall(const Vector3& pos, float r);
    void buildMirrorBall(const Vector3& pos, float r);
    void buildMixBall(const Vector3& pos, float r);

    void buildRedBall(const Vector3& pos, float r);
    void buildAquaBall(const Vector3& pos, float r);

    void buildBunny(const Vector3& pos, float scale);

    void buildRedTri(const Vector3& pos);
    void buildGreenTri(const Vector3& pos);

    void buildGlassTri(const Vector3& pos);

protected:
    ObjectPool* m_pObjectPool;
};

#endif