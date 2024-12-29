#include "simpleBunnySceneBuilder.h"
#include "materialDef.h"
#include "resourceDef.h"

void SimpleBunnySceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 80, 200), 20);
    
    buildBunny(Vector3(10, -90, 350), 300, ResourceDef::SIMPLE_BUNNY, MATERIAL_TYPE::M_DIELECTRIC);
}