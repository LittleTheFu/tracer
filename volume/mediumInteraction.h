#ifndef _MEDIUM_INTERACTION_H_
#define _MEDIUM_INTERACTION_H_

#include "vector.h"
#include "medium.h"

class MediumInteraction
{
public:
    bool isValid() const;
public:
    float t;
    Vector3 point;
    Vector3 wo;
    std::shared_ptr<Medium> medium;
};


#endif