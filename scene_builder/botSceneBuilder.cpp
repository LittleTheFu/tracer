#include "botSceneBuilder.h"
#include "resourceDef.h"

void BotSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 30, 220), 16);

    setLightIntensity(0, 30.0f);
    setLightIntensity(1, 30.0f);
    setLightIntensity(2, 30.0f);

    buildModel(Vector3(-10, -70, 300),
               0.3f,
               ResourceDef::BOT,
               MATERIAL_TYPE::M_MIRROR,
               false,
               false);
}
