#include "alphaSceneBuilder.h"
#include "config.h"

void AlphaSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 72, 250), 30);

    if (configBunnyType == BUNNY_TYPE::LOW_LOW)
        buildLowLowBunny(Vector3(10, -50, 250), 400);
    else if (configBunnyType == BUNNY_TYPE::LOW)
        buildLowBunny(Vector3(10, -50, 250), 400);
    else if (configBunnyType == BUNNY_TYPE::SIMPLE)
        buildSimpleBunny(Vector3(10, -50, 250), 400);
    else
        buildBunny(Vector3(10, -50, 250), 400);
}