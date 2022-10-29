#ifndef _R_MATERIAL_H_
#define _R_MATERIAL_H_

#include "brdf.h"
#include "hitinfo.h"

class Rmaterial
{
public:
    void eval(const HitInfo& info);
    Brdf* pBrdf;
};

#endif