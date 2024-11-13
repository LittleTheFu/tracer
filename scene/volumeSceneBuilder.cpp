#include "volumeSceneBuilder.h"
#include "config.h"

void VolumeSceneBuilder::build()
{
    buildRoom();
    buildLight(configLightPos, configLightRadius);
}