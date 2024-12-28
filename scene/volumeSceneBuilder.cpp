#include "volumeSceneBuilder.h"
#include "config.h"

void VolumeSceneBuilder::build()
{
    buildRoom();
    buildLight(configLightPos, configLightRadius);

    buildAquaBall(Vector3(-90, -90, 260), 5);
    buildVolumeBall(Vector3(0, 0, 320), 50);
    // buildBunny(Vector3(10, -90, 350), 1200, ResourceDef::LOW_LOW_BUNNY, MATERIAL_TYPE::M_NULL);
}