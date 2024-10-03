#ifndef _SCENE_H_
#define _SCENE_H_

#include "camera.h"
#include "objectpool.h"
#include "pinholeCamera.h"
#include "lambertianMaterial.h"
#include "mirrorMaterial.h"
#include "glassMaterial.h"
#include "mixMaterial.h"

class Scene
{
public:
    Scene(bool useSimpleTracer = true);

public:
    void run();

private:
    void preConstructScene();
    void constructScene();

    void preRender();
    void render();
    void postRender();

private:
    void createMaterials();

    void buildRoom();
    void buildLight();

    void buildSceneWithDefaultConfig();

    void buildMirrorBall();   
    void buildRedBall();
    void buildMixBall();

private:
    ObjectPool* m_pObjectPool;
    Camera* m_pCamera;

private:
    float rho;

    LambertianMaterial *lambMtrlLena;
    LambertianMaterial *lambMtrlChessboard;
    LambertianMaterial *lambUV;
    LambertianMaterial *lambNoise;

    LambertianMaterial *lambMtrlRed;
    LambertianMaterial *lambMtrlYellow;
    LambertianMaterial *lambMtrlAqua;
    LambertianMaterial *lambMtrlPurple;
    LambertianMaterial *lambMtrlGreen;
    LambertianMaterial *lambMtrlBlue;
    LambertianMaterial *lambMtrlWhite;

    MirrorMaterial *MtrlMirror;
    GlassMaterial *MtrlGlass;

    MixMaterial *MtrlMix;
};

#endif