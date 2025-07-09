#include "materialDef.h"
#include "resourceDef.h"
#include "teapotSceneBuilder.h"
#include "config.h"

void TeapotSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(configLightIntensityScale);

    buildModel(Vector3(0, -50, 400),
               25,
               ResourceDef::TEAPOT,
               MATERIAL_TYPE::M_GLASS,
               false,
               true);
}