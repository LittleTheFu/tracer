#include "materialDef.h"
#include "resourceDef.h"
#include "cornellSceneBuilder.h"

void CornellSceneBuilder::build()
{
    // buildRoom();
    // buildLight(Vector3(0, 30, 220), 10);
    // setLightIntensity(1, 30.0f);
    // setLightIntensity(2, 30.0f);

    buildModel(Vector3(0, 0, 400),
               2.0f,
               ResourceDef::ROOM,
               MATERIAL_TYPE::M_RED,
               false,
               false);

    applyLightIntensityScaleAll(16.0f);
    // setLightIntensity(0, 1000.0f);
}