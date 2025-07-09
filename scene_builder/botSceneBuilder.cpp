#include "botSceneBuilder.h"
#include "resourceDef.h"
#include "config.h"

void BotSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(configLightIntensityScale);

    buildModel(Vector3(0, -50, 450),
               1.0f,
               ResourceDef::BOT,
               MATERIAL_TYPE::M_MIRROR,
               false,
               false);
}
