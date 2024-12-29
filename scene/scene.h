#ifndef _SCENE_H_
#define _SCENE_H_

#include <memory>

#include "sceneDef.h"
#include "camera.h"
#include "objectpool.h"
#include "sceneBuilder.h"
#include "tracerDef.h"

class Scene
{
public:
    Scene(SceneType sceneType, float resolutionScale, int samplersPerPixel, int depth);

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
    bool isBVHOn(SceneType type) const;
    std::shared_ptr<SceneBuilder> createSceneBuilder(SceneType type) const;

private:
    std::shared_ptr<ObjectPool> m_pObjectPool;
    std::shared_ptr<Camera> m_pCamera;
    std::shared_ptr<SceneBuilder> m_pBuilder;
};

#endif