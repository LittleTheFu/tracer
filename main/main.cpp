#include <memory>

#include "config.h"
#include "scene.h"

int main()
{
    Scene scene(configScene, configResolutionScale, configSamplersPerPixel, configNeeTracerDepth);
    scene.run();

    return 0;
}