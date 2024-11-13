#include "bunnySceneBuilder.h"
#include "config.h"

void BunnySceneBuilder::build()
{
    buildRoom();
    buildLight(configLightPos, configLightRadius);
    
    buildBunny(Vector3(10, -50, 250), 400, configBunnyRes, configBunnyMaterial);
}