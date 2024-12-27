#ifndef _BETA_SCENE_BUILDER_H_
#define _BETA_SCENE_BUILDER_H_

#include "sceneBuilder.h"

class SimpleSceneBuilder : public SceneBuilder
{
public:
    virtual void build() override;
};

#endif