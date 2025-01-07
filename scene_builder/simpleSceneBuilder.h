#ifndef _BETA_SCENE_BUILDER_H_
#define _BETA_SCENE_BUILDER_H_

#include "sceneBuilder.h"

class SimpleSceneBuilder : public SceneBuilder
{
public:
    virtual void build() override;

private:
    virtual MATERIAL_TYPE getLeftWallMaterial() const override;
    virtual MATERIAL_TYPE getCeilingMaterial() const override;
};

#endif