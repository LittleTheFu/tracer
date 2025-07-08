#include "materialDef.h"
#include "resourceDef.h"
#include "cubeSceneBuilder.h"

void CubeSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(20.0f);

    buildModel(Vector3(-30, -30, 400),
               20,
               ResourceDef::SLAB,
               MATERIAL_TYPE::M_YELLOW,
               false,
               true);

    buildModel(Vector3(-30, 30, 300),
               20,
               ResourceDef::SLAB,
               MATERIAL_TYPE::M_RED,
               false,
               true);

    buildModel(Vector3(30, -30, 300),
               20,
               ResourceDef::SLAB,
               MATERIAL_TYPE::M_AQUA,
               false,
               true);

    buildModel(Vector3(30, 30, 300),
               20,
               ResourceDef::SLAB,
               MATERIAL_TYPE::M_GREEN,
               false,
               true);

    buildModel(Vector3(0, 0, 200),
               20,
               ResourceDef::SLAB,
               MATERIAL_TYPE::M_WHITE,
               false,
               true);
}