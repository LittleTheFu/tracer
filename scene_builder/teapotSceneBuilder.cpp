#include "materialDef.h"
#include "resourceDef.h"
#include "teapotSceneBuilder.h"

void TeapotSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(20.0f);

    buildModel(Vector3(-10, -60, 400),
               24,
               ResourceDef::TEAPOT,
               MATERIAL_TYPE::M_MICRO_FACET_TRANSMISSION,
               false,
               true);
}