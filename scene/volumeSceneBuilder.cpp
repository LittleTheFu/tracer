#include "volumeSceneBuilder.h"
#include "config.h"

void VolumeSceneBuilder::build()
{
    // buildRoom();
    buildLight(configLightPos, configLightRadius);

    buildVolumeBall(Vector3(0, -25, 320), 100);
    // buildBunny(Vector3(10, -90, 350), 1200, ResourceDef::LOW_LOW_BUNNY, MATERIAL_TYPE::M_NULL);
}