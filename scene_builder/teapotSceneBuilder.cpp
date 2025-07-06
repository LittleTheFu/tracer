#include "materialDef.h"
#include "resourceDef.h"
#include "teapotSceneBuilder.h"

void TeapotSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0,30,220), 16);
    setLightIntensity(0, 30.0f);
    setLightIntensity(1, 30.0f);
    setLightIntensity(2, 30.0f);

    buildModel(Vector3(-10, -60, 300),
               24,
               ResourceDef::TEAPOT,
               MATERIAL_TYPE::M_GLASS,
               true);
}