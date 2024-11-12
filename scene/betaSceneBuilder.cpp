#include "betaSceneBuilder.h"
#include "config.h"

void BetaSceneBuilder::build()
{
    // buildMeshRoom();
    buildRoom();
    buildLight(configLightPos, configLightRadius);

    buildRedBall(Vector3(-80, 0, 350), 20);
    buildAquaBall(Vector3(-70, 70, 250), 20);
    buildMirrorBall(Vector3(-50, 70, 350), 20);
    buildGlassBall(Vector3(45, 30, 300), 40);
    
    // buildRedTri(Vector3(55,-20,370));
    // buildGreenTri(Vector3(50,-60,350));
    // buildGlassTri(Vector3(20,35,230));
}