#include "mtrlSceneBuilder.h"

void MtrlSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0,70,160), 23);
    setLightIntensity(80.0f);

    buildMeasuredGreenBall(Vector3(-70, -30, 280), 20);
    buildMeasuredWhiteBall(Vector3(-25, -30, 280), 20);
    buildMeasuredMetalBall(Vector3(25, -30, 280), 20);
    buildMeasuredMintBall(Vector3(70, -30, 280), 20);
    
    buildMeasuredGreenPvcBall(Vector3(-70, 30, 280), 20);
    buildMeasuredBrushedAluminiumBall(Vector3(-25, 30, 280), 20);
    buildMeasuredTarkinTunicBall(Vector3(25, 30, 280), 20);
    buildMeasuredSariSilkBall(Vector3(70, 30, 280), 20);
}