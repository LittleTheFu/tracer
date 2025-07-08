#include "complexBunnySceneBuilder.h"
#include "materialDef.h"
#include "resourceDef.h"

void ComplexBunnyBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(20.0f);

    buildModel(Vector3(20, -90, 400),
               30,
               ResourceDef::COMPLEX_BUNNY,
               MATERIAL_TYPE::M_MEASURED_GREEN_PVC_BRDF,
               false);
}