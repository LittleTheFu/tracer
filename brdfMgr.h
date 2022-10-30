#ifndef _BRDF_MGR_H_
#define _BRDF_MGR_H_

#include "lambertian.h"

class BrdfMgr
{
public:
    BrdfMgr();
    ~BrdfMgr();

    Brdf* getRedBrdf();
    Brdf* getGreenBrdf();
    Brdf* getBlueBrdf();
    Brdf* getWhiteBrdf();

private:
    Brdf *brdfRed;
    Brdf *brdfGreen;
    Brdf *brdfBlue;
    Brdf *brdfWhite;
};

#endif