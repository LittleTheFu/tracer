#include "volumeSceneBuilder.h"
#include "config.h"

void VolumeSceneBuilder::build()
{
    // buildRoom();
    // buildLight(configLightPos, configLightRadius);

    buildVolumeBall(Vector3(-80, -40, 320), 20);
}