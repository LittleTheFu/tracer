#ifndef _SCENE_H_
#define _SCENE_H_

#include "camera.h"
#include "objectpool.h"
#include "pinholeCamera.h"

class Scene
{
public:
    Scene();

public:
    void run();

private:
    void constructScene();

    void preRender();
    void render();
    void postRender();

private:
    ObjectPool* m_pObjectPool;
    Camera* m_pCamera;
};

#endif