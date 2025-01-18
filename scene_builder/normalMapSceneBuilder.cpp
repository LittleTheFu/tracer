#include "normalMapSceneBuilder.h"

void NormalMapSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 10, 200), 20);
    setLightIntensity(60.0f);

    buildNormalMapGreenPvcBall(Vector3(35, -50, 270), 35);
    buildNormalMapSariSilkBall(Vector3(-35, -50, 270), 35);
}

MATERIAL_TYPE NormalMapSceneBuilder::getLeftWallMaterial() const
{
    return MATERIAL_TYPE::M_NORMAL_MAP_GREEN_PVC;
}

MATERIAL_TYPE NormalMapSceneBuilder::getRightWallMaterial() const
{
    return MATERIAL_TYPE::M_NORMAL_MAP_SARI_SILK;
}
