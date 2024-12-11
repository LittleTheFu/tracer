#include "bunnySceneBuilder.h"
#include "config.h"

void BunnySceneBuilder::build()
{
    buildRoom();
    buildLight(configLightPos, configLightRadius);
    
    buildBunny(Vector3(20, -70, 300), configBnuuyScale, configBunnyRes, configBunnyMaterial);
}