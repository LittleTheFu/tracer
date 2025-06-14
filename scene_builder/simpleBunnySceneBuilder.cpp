#include "simpleBunnySceneBuilder.h"
#include "materialDef.h"
#include "resourceDef.h"

void SimpleBunnySceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 0, 270), 10);
    setLightIntensity(60.0f);
    
    buildBunny(Vector3(30, -100, 350), 900, ResourceDef::SIMPLE_BUNNY, MATERIAL_TYPE::M_DIELECTRIC);
}

MATERIAL_TYPE SimpleBunnySceneBuilder::getCeilingMaterial() const
{
    return MATERIAL_TYPE::M_GREEN;
}
