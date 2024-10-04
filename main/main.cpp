#include "scene.h"
#include "mesh.h"
#include "common.h"
#include "tester.h"
#include "alphaSceneBuilder.h"
#include "betaSceneBuilder.h"

int main()
{
   
    // Tester tester;
    // tester.run();
    
    SceneBuilder* builder = new BetaSceneBuilder();
    Scene scene(builder);
    scene.run();

    return 0;
}