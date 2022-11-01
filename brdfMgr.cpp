#include "brdfMgr.h"
#include "color.h"
#include <iostream>

BrdfMgr::BrdfMgr()
{
    brdfRed = new Lambertian(Color::COLOR_RED * 0.20);
    brdfGreen = new Lambertian(Color::COLOR_GREEN * 0.20);
    brdfBlue = new Lambertian(Color::COLOR_BLUE * 0.20);
    brdfWhite = new Lambertian(Color::COLOR_WHITE * 0.20);
}

BrdfMgr::~BrdfMgr()
{
    std::cout<<"should release bdrf here!"<<std::endl;
    // if(brdf)
    // {
    //     delete brdf;
    //     brdf = nullptr;
    // }
}

Brdf* BrdfMgr::getRedBrdf()
{
    return brdfRed;
}

Brdf* BrdfMgr::getGreenBrdf()
{
    return brdfGreen;
}

Brdf* BrdfMgr::getBlueBrdf()
{
    return brdfBlue;
}

Brdf* BrdfMgr::getWhiteBrdf()
{
    return brdfWhite;
}