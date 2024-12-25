#ifndef _HIT_RECORD_H_
#define _HIT_RECORD_H_

#include "vector.h"
#include "material.h"
#include "transform.h"
#include "color.h"
#include "media.h"
// #include "geometry.h"
#include "brdf.h"
#include <memory>
#include <vector>

class Geometry;

class HitRecord
{
public:
    HitRecord();
    HitRecord getCloserOne(const HitRecord &that) const;

    Media getMeida(const Vector3 &dir) const;

    Media outsideMedia;
    Media insideMedia;
    
    Transform transform;
    std::shared_ptr<Brdf> brdf;
    std::shared_ptr<Geometry> geometry;
    bool isVolumeBoundery;

    Vector3 point;
    Vector3 normal;
    Vector3 reflect;
    float reflectPdf;

    Vector3 localPoint;

    float dotLight;
    float dot;
    Color f;

    float u;
    float v;

    // Vector3 dpdu;
    // Vector3 dpdv;

    float t;

    float t0;
    float t1;

    bool isMistHit;

    bool isDelta;
};

#endif