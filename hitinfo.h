#ifndef _HIT_INFO_H_
#define _HIT_INFO_H_

#include "vector.h"
#include "material.h"

class HitInfo
{
public:
    Vector3 m_point;
    Vector3 m_normal;
    Vector3 m_randomReflect;
    Material m_mtrl;
};

#endif