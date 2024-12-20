#include "scene.h"
#include "mesh.h"
#include "common.h"
#include "bunnySceneBuilder.h"
#include "betaSceneBuilder.h"
#include "volumeSceneBuilder.h"
#include "teapotSceneBuilder.h"
#include "config.h"
#include "mathUtility.h"
#include "vox.h"
#include <memory>
#include "powitacq_rgb.h"
std::shared_ptr<SceneBuilder> createBuilder()
{
    //test
    powitacq_rgb::BRDF b("../resource/ilm_l3_37_matte_rgb.bsdf");

    std::shared_ptr<SceneBuilder> builder = nullptr;
    
    if (configScene == ConfigScene::ROOM_BUNNY)
        builder = std::make_shared<BunnySceneBuilder>();
    else if (configScene == ConfigScene::ROOM_SIMPLE)
        builder = std::make_shared<BetaSceneBuilder>();
    else if (configScene == ConfigScene::ROOM_VOLUME)
        builder = std::make_shared<VolumeSceneBuilder>();
    else if (configScene == ConfigScene::ROOM_TEAPOT)
        builder = std::make_shared<TeapotSceneBuilder>();
    else
        builder = std::make_shared<BetaSceneBuilder>();

    return builder;
}

int main()
{
    Scene scene(createBuilder(), configTracerType);
    scene.run();

    return 0;
}