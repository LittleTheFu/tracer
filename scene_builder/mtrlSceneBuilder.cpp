#include "mtrlSceneBuilder.h"

void MtrlSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0,80,160), 16);
    setLightIntensity(80.0f);

    buildMeasuredGreenBall(Vector3(-70, -30, 280), 20);
    buildMeasuredWhiteBall(Vector3(-30, -30, 280), 20);
    buildMeasuredMetalBall(Vector3(30, -30, 280), 20);
    buildMeasuredMintBall(Vector3(70, -30, 280), 20);
    
    buildMeasuredGreenPvcBall(Vector3(-70, 30, 280), 20);
    buildMeasuredBrushedAluminiumBall(Vector3(-30, 30, 280), 20);
    buildMeasuredTarkinTunicBall(Vector3(30, 30, 280), 20);
    buildMeasuredSariSilkBall(Vector3(70, 30, 280), 20);
}