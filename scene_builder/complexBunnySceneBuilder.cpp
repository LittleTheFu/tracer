#include "complexBunnySceneBuilder.h"
#include "materialDef.h"
#include "resourceDef.h"

void ComplexBunnyBuilder::build()
{
    buildRoom();
    buildLight(Vector3(40, 50, 200), 10);
    setLightIntensity(60.0f);
    
    buildModel(Vector3(20, -90, 300), 50, ResourceDef::COMPLEX_BUNNY, MATERIAL_TYPE::M_MEASURED_GREEN_PVC_BRDF);
}