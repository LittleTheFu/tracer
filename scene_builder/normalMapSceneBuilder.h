#ifndef _NORMAL_MAP_SCENE_BUILDER_H_
#define _NORMAL_MAP_SCENE_BUILDER_H_

#include "sceneBuilder.h"

class NormalMapSceneBuilder : public SceneBuilder
{
public:
    virtual void build() override;

    virtual MATERIAL_TYPE getLeftWallMaterial() const;
    virtual MATERIAL_TYPE getRightWallMaterial() const;
};

#endif