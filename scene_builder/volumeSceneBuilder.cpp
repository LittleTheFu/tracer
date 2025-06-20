#include "config.h"
#include "volumeSceneBuilder.h"

void VolumeSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 80, 200), 20);

    // buildVolumeBall(Vector3(0, 0, 320), 100);
}