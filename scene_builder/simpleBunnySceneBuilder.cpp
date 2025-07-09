#include "simpleBunnySceneBuilder.h"
#include "materialDef.h"
#include "resourceDef.h"
#include "config.h"

void SimpleBunnySceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(configLightIntensityScale);

    buildModel(Vector3(30, -100, 400),
               700,
               ResourceDef::SIMPLE_BUNNY,
               MATERIAL_TYPE::M_YELLOW,
               false);
}

MATERIAL_TYPE SimpleBunnySceneBuilder::getCeilingMaterial() const
{
    return MATERIAL_TYPE::M_GREEN;
}
