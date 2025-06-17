#include "materialDef.h"
#include "resourceDef.h"
#include "teapotSceneBuilder.h"

void TeapotSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(30,30,250), 15);
    setLightIntensity(40.0f);
    
    buildModel(Vector3(-10, -60, 300), 24, ResourceDef::TEAPOT, MATERIAL_TYPE::M_MEASURED_GREEN_PVC_BRDF);
}