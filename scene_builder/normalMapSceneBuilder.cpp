#include "normalMapSceneBuilder.h"
#include "resourceDef.h"
#include "materialDef.h"
#include "config.h"

void NormalMapSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(configLightIntensityScale);
    
    buildModel(Vector3(-10, -60, 500), 24, ResourceDef::TEAPOT, MATERIAL_TYPE::M_MIRROR, true);
}

MATERIAL_TYPE NormalMapSceneBuilder::getLeftWallMaterial() const
{
    return MATERIAL_TYPE::M_YELLOW;
}

MATERIAL_TYPE NormalMapSceneBuilder::getRightWallMaterial() const
{
    return MATERIAL_TYPE::M_YELLOW;
}
