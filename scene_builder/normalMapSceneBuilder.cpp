#include "normalMapSceneBuilder.h"

void NormalMapSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 10, 200), 20);
    setLightIntensity(60.0f);

    buildNormalMapGreenPvcBall(Vector3(35, -50, 270), 35);
    buildNormalMapSariSilkBall(Vector3(-35, -50, 270), 35);
}