#include "config.h"
#include "volumeSceneBuilder.h"

void VolumeSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0, 80, 200), 10);
    setLightIntensity(0, 40);

    // buildVolumeBall(Vector3(0, 0, 320), 100);
}