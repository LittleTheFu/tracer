#ifndef _VOLUME_SCENE_BUILDER_H_
#define _VOLUME_SCENE_BUILDER_H_

#include "sceneBuilder.h"

class VolumeSceneBuilder : public SceneBuilder
{
public:
    virtual void build() override;
};


#endif