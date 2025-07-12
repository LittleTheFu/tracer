#include "botSceneBuilder.h"
#include "resourceDef.h"
#include "config.h"

void BotSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(configLightIntensityScale);

    buildModel(Vector3(0, -150, 440),
               1.0f,
               ResourceDef::BOT,
               MATERIAL_TYPE::M_MIRROR,
               false,
               false);
}
