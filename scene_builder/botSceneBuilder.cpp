#include "botSceneBuilder.h"
#include "resourceDef.h"

void BotSceneBuilder::build()
{
    // buildRoom();
    buildCornellRoom();
    buildLight(Vector3(0, 30, 220), 16);

    applyLightIntensityScale(0, 100.0f);
    applyLightIntensityScale(1, 30.0f);
    applyLightIntensityScale(2, 30.0f);

    buildModel(Vector3(-10, -70, 300),
               0.3f,
               ResourceDef::BOT,
               MATERIAL_TYPE::M_MIRROR,
               false,
               false);
}
