#ifndef _HIT_RECORD_H_
#define _HIT_RECORD_H_

#include "vector.h"
#include "rmaterial.h"

class HitRecord
{
public:
    Rmaterial mtrl;
    
    Vector3 point;
    Vector3 normal;
    Vector3 reflect;

    // Vector3 dpdu;
    // Vector3 dpdv;

    float t;
};

#endif