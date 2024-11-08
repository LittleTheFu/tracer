#include "scene.h"
#include "mesh.h"
#include "common.h"
#include "tester.h"
#include "bunnySceneBuilder.h"
#include "betaSceneBuilder.h"
#include "config.h"

int main()
{
    SceneBuilder *builder = nullptr;
    if (configUseBunnyScene)
        builder = new BunnySceneBuilder();
    else
        builder = new BetaSceneBuilder();

    Scene scene(builder, configUseSimpleTracer);

    if (configUseBatchRun)
        scene.batchRun();
    else
        scene.run();

    return 0;
}