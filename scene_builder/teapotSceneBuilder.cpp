#include "materialDef.h"
#include "resourceDef.h"
#include "teapotSceneBuilder.h"

void TeapotSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(30,30,200), 10);
    setLightIntensity(20.0f);
    
    buildBunny(Vector3(-10, -60, 300), 24, ResourceDef::TEAPOT, MATERIAL_TYPE::M_MEASURED_TARKIN_TUNIC_BRDF);
}