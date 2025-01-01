#include "simpleBunnySceneBuilder.h"
#include "materialDef.h"
#include "resourceDef.h"

void SimpleBunnySceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(40, 40, 350), 10);
    setLightIntensity(50.0f);
    
    buildBunny(Vector3(30, -100, 350), 900, ResourceDef::SIMPLE_BUNNY, MATERIAL_TYPE::M_DIELECTRIC);
}