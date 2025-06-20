#ifndef _INTERACTION_H_
#define _INTERACTION_H_

#include "vector.h"
#include <memory>
// #include <geometry.h>

class Primitive;
class Geometry;
class Material;
class Medium;

class Interaction
{
public:
    Interaction() = default;
    ~Interaction() = default;

    bool hasNormalMap() const;
    Vector3 getNormalFromNormalMap(float u, float v) const;

public:
    Vector3 incoming;
    Vector3 point;

    Vector3 normal_geometry;
    Vector3 normal_shading;

    bool is_surface_hit = false;
    bool is_volume_boundary_hit = false;

    Vector3 wo;

    float u;
    float v;

    // std::shared_ptr<Geometry> geometry;
    // std::shared_ptr<MaterialPlus> material;

    std::shared_ptr<Primitive> primitive = nullptr;
    std::shared_ptr<Medium> medium = nullptr;

    //---for refactoring---
    float t;
};

#endif