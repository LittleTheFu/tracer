#include "simpleBunnySceneBuilder.h"
#include "materialDef.h"
#include "resourceDef.h"

void SimpleBunnySceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(20.0f);

    buildModel(Vector3(30, -100, 400),
               900,
               ResourceDef::SIMPLE_BUNNY,
               MATERIAL_TYPE::M_AQUA,
               false);
}

MATERIAL_TYPE SimpleBunnySceneBuilder::getCeilingMaterial() const
{
    return MATERIAL_TYPE::M_GREEN;
}
