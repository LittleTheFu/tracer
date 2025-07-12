#include "materialDef.h"
#include "resourceDef.h"
#include "cornellSceneBuilder.h"
#include "config.h"

void CornellSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(configLightIntensityScale);

    buildModel(Vector3(50, -110, 400),
               20,
               ResourceDef::TEAPOT,
               MATERIAL_TYPE::M_MICRO_FACET_TRANSMISSION,
               false,
               true);

    buildModel(Vector3(-50, -110, 400),
               20,
               ResourceDef::TEAPOT,
               MATERIAL_TYPE::M_GLASS,
               false,
               true);
}