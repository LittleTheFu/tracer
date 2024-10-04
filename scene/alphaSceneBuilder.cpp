#include "alphaSceneBuilder.h"

void AlphaSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 0, 300), 50);
}