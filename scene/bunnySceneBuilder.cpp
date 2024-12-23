#include "bunnySceneBuilder.h"
#include "config.h"

void BunnySceneBuilder::build()
{
    buildRoom();
    buildLight(configLightPos, configLightRadius);
    
    // buildBunny(Vector3(10, -50, 350), configBnuuyScale, configBunnyRes, configBunnyMaterial);
    buildBunny(Vector3(10, -90, 350), configBnuuyScale, configBunnyRes, configBunnyMaterial);
}