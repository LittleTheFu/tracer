#ifndef _HIT_RECORD_H_
#define _HIT_RECORD_H_

#include "vector.h"
#include "material.h"
#include "transform.h"
#include "color.h"

class HitRecord
{
public:
    HitRecord();
    
    Transform transform;
    Material mtrl;

    Vector3 point;
    Vector3 normal;
    Vector3 reflect;
    float reflectPdf;

    float dot;
    Color f;

    float u;
    float v;

    // Vector3 dpdu;
    // Vector3 dpdv;

    float t;

    bool isMirror;
};

#endif