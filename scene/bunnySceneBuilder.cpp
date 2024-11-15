#include "bunnySceneBuilder.h"
#include "config.h"

void BunnySceneBuilder::build()
{
    buildRoom();
    buildLight(configLightPos, configLightRadius);
    
    buildBunny(Vector3(10, -60, 350), configBnuuyScale, configBunnyRes, configBunnyMaterial);
}