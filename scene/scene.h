#ifndef _SCENE_H_
#define _SCENE_H_

#include "camera.h"
#include "objectpool.h"
#include "sceneBuilder.h"

class Scene
{
public:
    Scene(SceneBuilder *pBuilder, bool useSimpleTracer = true);

public:
    void run();
    void batchRun();

private:
    void preConstructScene();
    void constructScene();

    void preRender();
    void render();
    void postRender();

private:
    ObjectPool* m_pObjectPool;
    Camera* m_pCamera;
    SceneBuilder* m_pBuilder;

    int m_MaxBounces;
};

#endif