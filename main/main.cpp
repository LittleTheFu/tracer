#include "scene.h"
#include "mesh.h"
#include "common.h"
#include "tester.h"
#include "alphaSceneBuilder.h"
#include "betaSceneBuilder.h"

int main()
{
    int scene_id = 1;

    SceneBuilder *builder = nullptr;
    if (scene_id == 0)
        builder = new AlphaSceneBuilder();
    else
        builder = new BetaSceneBuilder();

    Scene scene(builder);
    scene.run();

    return 0;
}