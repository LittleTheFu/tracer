#include "materialDef.h"
#include "resourceDef.h"
#include "teapotSceneBuilder.h"
#include "config.h"

void TeapotSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(configLightIntensityScale);

    buildModel(Vector3(10, -150, 500),
               30,
               ResourceDef::TEAPOT,
               MATERIAL_TYPE::M_MIRROR,
               true,
               true);
}