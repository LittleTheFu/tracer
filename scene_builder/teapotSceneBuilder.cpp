#include "materialDef.h"
#include "resourceDef.h"
#include "teapotSceneBuilder.h"

void TeapotSceneBuilder::build()
{
    // buildRoom();
    buildCornellRoom();

    buildLight(Vector3(0, 30, 220), 16);
    applyLightIntensityScale(0, 30.0f);
    applyLightIntensityScale(1, 30.0f);
    applyLightIntensityScale(2, 30.0f);

    buildModel(Vector3(-10, -60, 300),
               24,
               ResourceDef::TEAPOT,
               MATERIAL_TYPE::M_MICRO_FACET_TRANSMISSION,
               false,
               true);
}