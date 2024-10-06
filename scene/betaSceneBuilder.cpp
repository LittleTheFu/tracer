#include "betaSceneBuilder.h"

void BetaSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 0, 300), 10);

    buildRedBall(Vector3(70, 70, 350), 20);
    
    buildRedTri(Vector3(-50,60,330));
    // buildGreenTri(Vector3(50,-60,330));

    // buildBunny(Vector3(-60,-60,350), 300);
}