#include "mtrlSceneBuilder.h"

void MtrlSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0,40,300), 16);
}