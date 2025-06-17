#include "materialDef.h"
#include "resourceDef.h"
#include "teapotSceneBuilder.h"

void TeapotSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(30,30,250), 10);
    setLightIntensity(60.0f);
    
    buildModel(Vector3(-10, -60, 300), 24, ResourceDef::TEAPOT, MATERIAL_TYPE::M_GLASS);
}