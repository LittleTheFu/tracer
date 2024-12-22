#ifndef _SCENE_H_
#define _SCENE_H_

#include "camera.h"
#include "objectpool.h"
#include "sceneBuilder.h"
#include "tracerDef.h"
#include <memory>

class Scene
{
public:
    Scene(std::shared_ptr<SceneBuilder> pBuilder, TracerType tracerType);

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
    std::shared_ptr<ObjectPool> m_pObjectPool;
    std::shared_ptr<Camera> m_pCamera;
    std::shared_ptr<SceneBuilder> m_pBuilder;
};

#endif