#include "bunnySceneBuilder.h"
#include "config.h"

void BunnySceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 72, 250), 30);
    
    buildRealBunny(Vector3(10, -50, 250), 400, configBunnyRes, configBunnyMaterial);
}