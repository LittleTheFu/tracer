#include "scene.h"
#include "mesh.h"
#include "common.h"
#include "tester.h"
#include "alphaSceneBuilder.h"

int main()
{
   
    // Tester tester;
    // tester.run();
    
    SceneBuilder* builder = new AlphaSceneBuilder();
    Scene scene(builder);
    scene.run();

    return 0;
}