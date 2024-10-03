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
    void build();

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