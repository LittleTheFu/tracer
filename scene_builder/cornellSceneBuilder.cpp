#include "materialDef.h"
#include "resourceDef.h"
#include "cornellSceneBuilder.h"

void CornellSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(20.0f);
}