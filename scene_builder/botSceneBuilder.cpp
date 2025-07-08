#include "botSceneBuilder.h"
#include "resourceDef.h"

void BotSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(20.0f);

    buildModel(Vector3(0, -100, 340),
               0.5f,
               ResourceDef::BOT,
               MATERIAL_TYPE::M_MIRROR,
               false,
               false);
}
