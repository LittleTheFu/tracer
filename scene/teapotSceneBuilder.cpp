#include "teapotSceneBuilder.h"
#include "resourceDef.h"
#include "materialDef.h"

void TeapotSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0,40,300), 16);
    
    buildBunny(Vector3(10, -60, 300), 24, ResourceDef::TEAPOT, MATERIAL_TYPE::M_COMBINED);
}