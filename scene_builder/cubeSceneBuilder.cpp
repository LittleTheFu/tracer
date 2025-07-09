#include "materialDef.h"
#include "resourceDef.h"
#include "cubeSceneBuilder.h"
#include "config.h"

void CubeSceneBuilder::build()
{
    buildCornellRoom();
    // buildRoom();
    // buildLight(Vector3(0, 80, 350), 1);
    applyLightIntensityScaleAll(configLightIntensityScale);

    buildModel(Vector3(40, 80, 400),
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

    buildModel(Vector3(-30, -30, 100),
               20,
               ResourceDef::SLAB,
               MATERIAL_TYPE::M_AQUA,
               false,
               true);

    buildModel(Vector3(-70, 30, 400),
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