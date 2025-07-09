#include "materialDef.h"
#include "resourceDef.h"
#include "cubeSceneBuilder.h"
#include "config.h"

void CubeSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(configLightIntensityScale);

    buildModel(Vector3(40, 20, 400),
               20,
               ResourceDef::CUBE,
               MATERIAL_TYPE::M_AQUA,
               false,
               true);

    buildModel(Vector3(40, 20, 500),
               50,
               ResourceDef::SLAB,
               MATERIAL_TYPE::M_WHITE,
               false,
               true);

    buildModel(Vector3(-30, -30, 400),
               20,
               ResourceDef::SLAB,
               MATERIAL_TYPE::M_AQUA,
               false,
               true);

    buildModel(Vector3(-30, 30, 400),
               20,
               ResourceDef::SLAB,
               MATERIAL_TYPE::M_GREEN,
               false,
               true);

    // buildModel(Vector3(0, 0, 200),
    //            20,
    //            ResourceDef::CUBE,
    //            MATERIAL_TYPE::M_GLASS,
    //            false,
    //            true);
}