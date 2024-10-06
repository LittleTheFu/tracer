#include "betaSceneBuilder.h"

void BetaSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, -50, 300), 10);

    // buildRedBall(Vector3(70, 70, 350), 20);
    
    // buildRedTri(Vector3(0,0,360));
    // buildGreenTri(Vector3(50,-60,360));

    buildBunny(Vector3(10, 10, 350), 500);
}