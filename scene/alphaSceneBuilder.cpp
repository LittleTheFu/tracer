#include "alphaSceneBuilder.h"

void AlphaSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 72, 250), 30);

    buildBunny(Vector3(10, -50, 250), 400);
}