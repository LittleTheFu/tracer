#include "betaSceneBuilder.h"

void BetaSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 70, 300), 10);

    // buildRedBall(Vector3(70, 70, 350), 20);
    // buildMirrorBall(Vector3(-50, 70, 350), 20);
    
    buildRedTri(Vector3(30,35,250));
    buildGreenTri(Vector3(50,-60,350));

    // buildBunny(Vector3(10, 10, 350), 500);
}