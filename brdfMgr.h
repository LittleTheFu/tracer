#ifndef _BRDF_MGR_H_
#define _BRDF_MGR_H_

#include "brdf.h"

class BrdfMgr
{
public:
    BrdfMgr();
    ~BrdfMgr();

    Brdf* getRedBrdf();
    Brdf* getGreenBrdf();
    Brdf* getBlueBrdf();
    Brdf* getWhiteBrdf();
    Brdf* getYellowBrdf();
    Brdf* getAquaBrdf();
    Brdf* getPurpleBrdf();

    Brdf* getMirrorBrdf();
    Brdf* getGlassBrdf();

private:
    Brdf *brdfRed;
    Brdf *brdfGreen;
    Brdf *brdfBlue;
    Brdf *brdfWhite;
    Brdf *brdfAqua;
    Brdf *brdfYellow;
    Brdf *brdfPurple;

    Brdf *brdfMirror;
    Brdf *brdfGlass;
};

#endif