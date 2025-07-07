#include "materialDef.h"
#include "resourceDef.h"
#include "cubeSceneBuilder.h"

void CubeSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 30, 220), 5);
    setLightIntensity(0, 160.0f);
    // setLightIntensity(1, 30.0f);
    // setLightIntensity(2, 30.0f);

    buildModel(Vector3(-10, 0, 300),
               30,
               ResourceDef::SLAB,
               MATERIAL_TYPE::M_AQUA,
               false,
               true);

    buildModel(Vector3(-10, 0, 280),
               20,
               ResourceDef::SLAB,
               MATERIAL_TYPE::M_GLASS,
               false,
               true);
}