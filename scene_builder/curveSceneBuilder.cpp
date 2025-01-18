#include "curveSceneBuilder.h"

void CurveSceneBuilder::build()
{
    // buildRoom();
    buildLight(Vector3(0, 70, 160), 23);
    setLightIntensity(80.0f);

    buildRedCurve(Vector3(-70, -30, 280));
}