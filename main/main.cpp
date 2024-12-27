#include "scene.h"
#include "mesh.h"
#include "common.h"
#include "simpleBunnySceneBuilder.h"
#include "simpleSceneBuilder.h"
#include "volumeSceneBuilder.h"
#include "teapotSceneBuilder.h"
#include "mtrlSceneBuilder.h"
#include "config.h"
#include "mathUtility.h"
#include "vox.h"
#include <memory>

std::shared_ptr<SceneBuilder> createBuilder()
{
    std::shared_ptr<SceneBuilder> builder = nullptr;
    
    if (configScene == ConfigScene::ROOM_BUNNY)
        builder = std::make_shared<SimpleBunnySceneBuilder>();
    else if (configScene == ConfigScene::ROOM_SIMPLE)
        builder = std::make_shared<SimpleSceneBuilder>();
    else if (configScene == ConfigScene::ROOM_VOLUME)
        builder = std::make_shared<VolumeSceneBuilder>();
    else if (configScene == ConfigScene::ROOM_TEAPOT)
        builder = std::make_shared<TeapotSceneBuilder>();
    else if (configScene == ConfigScene::ROOM_MATERIAL_BALLS)
        builder = std::make_shared<MtrlSceneBuilder>();
    else
        builder = std::make_shared<SimpleSceneBuilder>();

    return builder;
}

int main()
{
    Scene scene(createBuilder(), configTracerType);
    scene.run();

    return 0;
}