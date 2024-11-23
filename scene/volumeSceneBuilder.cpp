#include "volumeSceneBuilder.h"
#include "config.h"

void VolumeSceneBuilder::build()
{
    // buildRoom();
    // buildLight(configLightPos, configLightRadius);

    buildVolumeBall(Vector3(0, 0, 320), 80);
}