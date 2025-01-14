#include "materialDef.h"
#include "resourceDef.h"
#include "teapotSceneBuilder.h"

void TeapotSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0,30,200), 20);
    setLightIntensity(80.0f);
    
    buildBunny(Vector3(-10, -60, 300), 24, ResourceDef::TEAPOT, MATERIAL_TYPE::M_MEASURED_TARKIN_TUNIC_BRDF);
}