#include "materialDef.h"
#include "resourceDef.h"
#include "cornellSceneBuilder.h"
#include "config.h"

void CornellSceneBuilder::build()
{
    buildCornellRoom();
    applyLightIntensityScaleAll(configLightIntensityScale);
}