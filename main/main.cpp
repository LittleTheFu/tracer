#include "scene.h"
#include "mesh.h"
#include "common.h"
#include "tester.h"
#include "sceneBuilder.h"

int main()
{
   
    // Tester tester;
    // tester.run();
    
    SceneBuilder* builder = new SceneBuilder();
    Scene scene(builder);
    scene.run();

    return 0;
}