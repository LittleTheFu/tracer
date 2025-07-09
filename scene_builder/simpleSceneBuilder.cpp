#include "simpleSceneBuilder.h"
#include "config.h"

void SimpleSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(configLightIntensityScale);

    buildRedBall(Vector3(60, 70, 350), 20);
    buildAquaBall(Vector3(-70, 80, 400), 20);

    //to be fixed : light power leak
    buildGlassBall(Vector3(50, -60, 350), 30);
    
    buildRedTri(Vector3(-55,0,350));
    buildGreenTri(Vector3(50,0,350));

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
