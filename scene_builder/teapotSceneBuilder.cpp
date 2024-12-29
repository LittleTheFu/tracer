#include "materialDef.h"
#include "resourceDef.h"
#include "teapotSceneBuilder.h"

void TeapotSceneBuilder::build()
{
    buildRoom();
    buildLight(Vector3(0,30,200), 16);
    
    buildBunny(Vector3(-10, -60, 300), 24, ResourceDef::TEAPOT, MATERIAL_TYPE::M_CHESSBOARD);
}