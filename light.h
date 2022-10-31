#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "geometry.h"

class Light
{
public:
    Light();

    Geometry *m_pGeometry;
    Rmaterial m_mtrl;
};

#endif