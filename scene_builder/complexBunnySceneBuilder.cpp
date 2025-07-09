#include "complexBunnySceneBuilder.h"
#include "materialDef.h"
#include "resourceDef.h"
#include "config.h"

void ComplexBunnyBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(configLightIntensityScale);

    buildModel(Vector3(20, -90, 400),
               30,
               ResourceDef::COMPLEX_BUNNY,
               MATERIAL_TYPE::M_MEASURED_GREEN_PVC_BRDF,
               false);
}