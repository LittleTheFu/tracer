#include "mtrlSceneBuilder.h"

void MtrlSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0,0,200), 16);

    buildMeasuredGreenBall(Vector3(-70, -30, 280), 20);
    buildMeasuredWhiteBall(Vector3(-30, -30, 280), 20);
    buildMeasuredMetalBall(Vector3(30, -30, 280), 20);
    buildMeasuredMintBall(Vector3(70, -30, 280), 20);
}