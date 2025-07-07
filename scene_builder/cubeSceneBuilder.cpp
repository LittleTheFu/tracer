#include "materialDef.h"
#include "resourceDef.h"
#include "cubeSceneBuilder.h"

void CubeSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 30, 180), 12);
    setLightIntensity(0, 160.0f);
    // setLightIntensity(1, 30.0f);
    // setLightIntensity(2, 30.0f);

    buildModel(Vector3(-10, 0, 300),
               30,
               ResourceDef::SLAB,
               MATERIAL_TYPE::M_YELLOW,
               false,
               true);

    buildModel(Vector3(10, 0, 220),
               20,
               ResourceDef::SLAB,
               MATERIAL_TYPE::M_MICRO_FACET_TRANSMISSION,
               false,
               true);
}