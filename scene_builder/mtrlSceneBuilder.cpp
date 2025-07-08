#include "mtrlSceneBuilder.h"
#include "config.h"

void MtrlSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(configLightIntensityScale);
    
    buildMeasuredGreenPvcBall(Vector3(-70, 30, 400), 20);
    // buildMeasuredBrushedAluminiumBall(Vector3(-25, 30, 280), 20);
    buildMeasuredTarkinTunicBall(Vector3(25, 30, 400), 20);
    buildMeasuredSariSilkBall(Vector3(70, 30, 400), 20);
}