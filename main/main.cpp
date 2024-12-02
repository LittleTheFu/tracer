#include "scene.h"
#include "mesh.h"
#include "common.h"
#include "bunnySceneBuilder.h"
#include "betaSceneBuilder.h"
#include "volumeSceneBuilder.h"
#include "config.h"
#include "mathUtility.h"
#include "vox.h"
#include <memory>
std::shared_ptr<SceneBuilder> createBuilder()
{
    std::shared_ptr<SceneBuilder> builder = nullptr;
    
    if (configScene == ConfigScene::ROOM_BUNNY)
        builder = std::make_shared<BunnySceneBuilder>();
    else if (configScene == ConfigScene::ROOM_SIMPLE)
        builder = std::make_shared<BetaSceneBuilder>();
    else if (configScene == ConfigScene::ROOM_VOLUME)
        builder = std::make_shared<VolumeSceneBuilder>();
    else
        builder = std::make_shared<BetaSceneBuilder>();

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
    scene.run();

    return 0;
}