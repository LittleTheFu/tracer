#include "normalMapSceneBuilder.h"
#include "resourceDef.h"
#include "materialDef.h"

void NormalMapSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(30,30,250), 15);
    setLightIntensity(0, 40.0f);
    
    buildModel(Vector3(-10, -60, 300), 24, ResourceDef::TEAPOT, MATERIAL_TYPE::M_MIRROR, true);
}

MATERIAL_TYPE NormalMapSceneBuilder::getLeftWallMaterial() const
{
    return MATERIAL_TYPE::M_NORMAL_MAP_GREEN_PVC;
}

MATERIAL_TYPE NormalMapSceneBuilder::getRightWallMaterial() const
{
    return MATERIAL_TYPE::M_NORMAL_MAP_SARI_SILK;
}
