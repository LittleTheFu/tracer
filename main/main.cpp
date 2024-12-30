#include <string>
#include <memory>

#include "config.h"
#include "scene.h"
#include "sceneDef.h"

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        std::string str = argv[1];
        if (str == "simple_room")
            configScene = SceneType::ROOM_SIMPLE;
        else if (str == "simple_room_bunny")
            configScene = SceneType::ROOM_SIMPLE_BUNNY;
        else if (str == "complex_room_bunny")
            configScene = SceneType::ROOM_COMPLEX_BUNNY;
        else if (str == "room_teapot")
            configScene = SceneType::ROOM_TEAPOT;
        else if (str == "room_material_balls")
            configScene = SceneType::ROOM_MATERIAL_BALLS;
        else
        {
            // do nothing
        }
    }

    Scene scene(configScene, configResolutionScale, configSamplersPerPixel, configNeeTracerDepth);
    scene.run();

    return 0;
}