#include "scene.h"
#include "mesh.h"
#include "common.h"
#include "tester.h"
#include "bunnySceneBuilder.h"
#include "betaSceneBuilder.h"
#include "volumeSceneBuilder.h"
#include "config.h"

SceneBuilder* createBuilder()
{
    SceneBuilder *builder = nullptr;
    
    if (configScene == ConfigScene::ROOM_BUNNY)
        builder = new BunnySceneBuilder();
    else if (configScene == ConfigScene::ROOM_SIMPLE)
        builder = new BetaSceneBuilder();
    else if (configScene == ConfigScene::ROOM_VOLUME)
        builder = new VolumeSceneBuilder();
    else
        builder = new BetaSceneBuilder();

    return builder;
}

int main()
{
    Scene scene(createBuilder(), configUseSimpleTracer);

    if (configUseBatchRun)
        scene.batchRun();
    else
        scene.run();

    return 0;
}