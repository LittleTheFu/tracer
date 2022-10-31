#ifndef _HIT_RECORD_H_
#define _HIT_RECORD_H_

#include "vector.h"
#include "rmaterial.h"
#include "transform.h"
#include "color.h"

class HitRecord
{
public:
    Transform transform;
    Rmaterial mtrl;

    Vector3 point;
    Vector3 normal;
    Vector3 reflect;
    float reflectPdf;

    float dot;
    Color f;

    // Vector3 dpdu;
    // Vector3 dpdv;

    float t;
};

#endif