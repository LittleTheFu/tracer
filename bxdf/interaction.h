#ifndef _INTERACTION_H_
#define _INTERACTION_H_

#include "vector.h"
#include <memory>
// #include "primitive.h"
// #include <geometry.h>
// #include "materialPlus.h"

class Primitive;
class Geometry;
class MaterialPlus;

class Interaction
{
public:
    Interaction() = default;
    ~Interaction() = default;

public:
    Vector3 incoming;
    Vector3 point;

    Vector3 normal_geometry;
    Vector3 normal_shading;

    Vector3 wo;

    float u;
    float v;

    // std::shared_ptr<Geometry> geometry;
    // std::shared_ptr<MaterialPlus> material;

    std::shared_ptr<Primitive> primitive;

    //---for refactoring---
    float t;
};

#endif