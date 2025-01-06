#include <string>
#include <memory>

#include "config.h"
#include "scene.h"
#include "sceneDef.h"

void configFromParams(int argc, char *argv[])
{
    if (argc < 2)
        return;

    if (!argv)
        return;

    if (!argv[1])
        return;

    std::string str = argv[1];
    if (str == "simple_room")
    {
        configScene = SceneType::ROOM_SIMPLE;
        configOutputImageName = "simple_room";
    }
    else if (str == "simple_room_bunny")
    {
        configScene = SceneType::ROOM_SIMPLE_BUNNY;
        configOutputImageName = "simple_room_bunny";
    }
    else if (str == "complex_room_bunny")
    {
        configScene = SceneType::ROOM_COMPLEX_BUNNY;
        configOutputImageName = "complex_room_bunny";
    }
    else if (str == "room_teapot")
    {
        configScene = SceneType::ROOM_TEAPOT;
        configOutputImageName = "room_teapot";
    }
    else if (str == "room_material_balls")
    {
        configScene = SceneType::ROOM_MATERIAL_BALLS;
        configOutputImageName = "room_material_balls";
    }
    else if (str == "room_normal_map")
    {
        configScene = SceneType::ROOM_NORMAL_MAP;
        configOutputImageName = "room_normal_map";
    }
    else
    {
        // do nothing
    }
}

int main(int argc, char *argv[])
{
    configFromParams(argc, argv);

    Scene scene(configScene, configResolutionScale, configSamplersPerPixel, configNeeTracerDepth);
    scene.run();

    return 0;
}