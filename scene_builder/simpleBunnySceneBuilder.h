#ifndef _ALPHA_SCENE_BUILDER_H_
#define _ALPHA_SCENE_BUILDER_H_

#include "sceneBuilder.h"

class SimpleBunnySceneBuilder : public SceneBuilder
{
public:
    virtual void build() override;

private:
    virtual MATERIAL_TYPE getCeilingMaterial() const override;
};

#endif