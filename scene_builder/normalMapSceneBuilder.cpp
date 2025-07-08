#include "normalMapSceneBuilder.h"
#include "resourceDef.h"
#include "materialDef.h"

void NormalMapSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(20.0f);
    
    buildModel(Vector3(-10, -60, 400), 24, ResourceDef::TEAPOT, MATERIAL_TYPE::M_MIRROR, true);
}

MATERIAL_TYPE NormalMapSceneBuilder::getLeftWallMaterial() const
{
    return MATERIAL_TYPE::M_NORMAL_MAP_GREEN_PVC;
}

MATERIAL_TYPE NormalMapSceneBuilder::getRightWallMaterial() const
{
    return MATERIAL_TYPE::M_NORMAL_MAP_SARI_SILK;
}
