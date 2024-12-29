#include "complexBunnyBuilder.h"
#include "materialDef.h"
#include "resourceDef.h"
void ComplexBunnyBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 80, 200), 20);
    
    buildBunny(Vector3(10, -90, 350), 300, ResourceDef::BUNNY, MATERIAL_TYPE::M_MEASURED_TARKIN_TUNIC_BRDF);
}