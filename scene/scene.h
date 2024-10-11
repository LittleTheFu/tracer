#ifndef _SCENE_H_
#define _SCENE_H_

#include "camera.h"
#include "objectpool.h"
#include "pinholeCamera.h"
#include "lambertianMaterial.h"
#include "mirrorMaterial.h"
#include "glassMaterial.h"
#include "mixMaterial.h"
#include "sceneBuilder.h"
#include "bvh.h"

class Scene
{
public:
    Scene(SceneBuilder *pBuilder, bool useSimpleTracer = true);

public:
    void run();

private:
    void preConstructScene();
    void constructScene();

    void preRender();
    void render();
    void postRender();



private:
    ObjectPool* m_pObjectPool;
    BVH* m_pBVH;
    Camera* m_pCamera;
    SceneBuilder* m_pBuilder;
    BVH*    m_pBvh;
};

#endif