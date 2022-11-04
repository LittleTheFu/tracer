#include "brdfMgr.h"
#include "color.h"
#include <iostream>

BrdfMgr::BrdfMgr()
{
    brdfRed = new Lambertian(Color::COLOR_RED * 0.5);
    brdfGreen = new Lambertian(Color::COLOR_GREEN * 0.5);
    brdfBlue = new Lambertian(Color::COLOR_BLUE * 0.5);
    brdfWhite = new Lambertian(Color::COLOR_WHITE * 0.5);
    brdfYellow = new Lambertian(Color::COLOR_YELLOW * 0.5);
    brdfAqua = new Lambertian(Color::COLOR_AQUA * 0.5);
}

BrdfMgr::~BrdfMgr()
{
    std::cout << "should release bdrf here!" << std::endl;
    // if(brdf)
    // {
    //     delete brdf;
    //     brdf = nullptr;
    // }
}

Brdf *BrdfMgr::getRedBrdf()
{
    return brdfRed;
}

Brdf *BrdfMgr::getGreenBrdf()
{
    return brdfGreen;
}

Brdf *BrdfMgr::getBlueBrdf()
{
    return brdfBlue;
}

Brdf *BrdfMgr::getWhiteBrdf()
{
    return brdfWhite;
}

Brdf *BrdfMgr::getYellowBrdf()
{
    return brdfYellow;
}

Brdf *BrdfMgr::getAquaBrdf()
{
    return brdfAqua;
}