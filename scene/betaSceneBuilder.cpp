#include "betaSceneBuilder.h"

void BetaSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 0, 300), 50);

    buildRedBall(Vector3(70, 70, 350), 20);
}