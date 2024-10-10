#include "betaSceneBuilder.h"

void BetaSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 70, 300), 30);

    buildRedBall(Vector3(70, 70, 250), 20);
    // buildMirrorBall(Vector3(-50, 70, 350), 20);
    // buildGlassBall(Vector3(45, 30, 350), 40);
    
    // buildRedTri(Vector3(55,-20,370));
    // buildGreenTri(Vector3(50,-60,350));
    // buildGlassTri(Vector3(20,35,230));

    // buildBunny(Vector3(10, 10, 370), 300);
}