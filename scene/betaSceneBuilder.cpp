#include "betaSceneBuilder.h"
#include "config.h"

void BetaSceneBuilder::build()
{
    // buildMeshRoom();
    buildRoom();
    buildLight(configLightPos, configLightRadius);

    buildConductorBall(Vector3(-10, -40, 300), 30);
    // buildRedBall(Vector3(-10, -70, 300), 20);
    // buildAquaBall(Vector3(-70, 80, 350), 20);
    // buildMirrorBall(Vector3(-50, 70, 350), 20);

    //to be fixed : light power leak
    // buildGlassBall(Vector3(60, 30, 300), 20);
    // buildMixBall(Vector3(50, -60, 300), 35);
    
    // buildRedTri(Vector3(-55,0,370));
    // buildGreenTri(Vector3(50,-60,350));

    //to be fixed : light power leak
    // buildGlassTri(Vector3(20,35,230));
}