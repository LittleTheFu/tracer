#include "scene.h"
#include "mesh.h"
#include "common.h"
#include "bunnySceneBuilder.h"
#include "betaSceneBuilder.h"
#include "volumeSceneBuilder.h"
#include "config.h"
#include "mathUtility.h"
#include "vox.h"
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

void testSample()
{
    for(int i = 0; i < 100; i++)
    {
        std::cout << MathUtility::sampleExponential(2) << std::endl;
    }
}

int main()
{
    Scene scene(createBuilder(), configTracerType);

    if (configUseBatchRun)
        scene.batchRun();
    else
        scene.run();

    return 0;
}