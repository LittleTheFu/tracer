#include "simpleSceneBuilder.h"

void SimpleSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 10, 200), 20);
    setLightIntensity(50.0f);

    // buildConductorBall(Vector3(-10, -40, 350), 50);
    buildRedBall(Vector3(60, 30, 300), 20);
    buildAquaBall(Vector3(-70, 80, 350), 20);
    // buildMirrorBall(Vector3(-50, 70, 350), 20);

    //to be fixed : light power leak
    // buildGlassBall(Vector3(60, 30, 300), 20);
    buildMixBall(Vector3(35, -50, 270), 35);
    
    buildRedTri(Vector3(-55,0,370));
    buildGreenTri(Vector3(50,-60,350));

    //to be fixed : light power leak
    // buildGlassTri(Vector3(20,35,230));
}

MATERIAL_TYPE SimpleSceneBuilder::getLeftWallMaterial() const
{
    return MATERIAL_TYPE::M_GREEN;
}

MATERIAL_TYPE SimpleSceneBuilder::getCeilingMaterial() const
{
    return MATERIAL_TYPE::M_WHITE;
}
