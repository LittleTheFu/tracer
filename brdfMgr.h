#ifndef _BRDF_MGR_H_
#define _BRDF_MGR_H_

#include "lambertian.h"

class BrdfMgr
{
public:
    BrdfMgr();
    ~BrdfMgr();
    Brdf* getBrdf();

private:
    Brdf *brdf;
};

#endif