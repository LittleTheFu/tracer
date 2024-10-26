#include "scene.h"
#include "mesh.h"
#include "common.h"
#include "tester.h"
#include "alphaSceneBuilder.h"
#include "betaSceneBuilder.h"
#include "config.h"

int main()
{
    SceneBuilder *builder = nullptr;
    if (configUseAlphaScene)
        builder = new AlphaSceneBuilder();
    else
        builder = new BetaSceneBuilder();

    Scene scene(builder);
    scene.run();

    return 0;
}