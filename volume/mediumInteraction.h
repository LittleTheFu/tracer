#ifndef _MEDIUM_INTERACTION_H_
#define _MEDIUM_INTERACTION_H_

#include "vector.h"
#include "medium.h"

class MediumInteraction
{
public:
    Vector3 pos;
    Vector3 wo;
    std::shared_ptr<const Medium> medium;
};


#endif