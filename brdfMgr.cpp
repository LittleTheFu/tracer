#include "brdfMgr.h"
#include "color.h"
#include "lambertian.h"
#include "mirror.h"
#include "glass.h"
#include <iostream>

BrdfMgr::BrdfMgr()
{
    brdfRed = new Lambertian(Color::COLOR_RED * 0.3);

    brdfGreen = new Lambertian(Color::COLOR_GREEN * 0.3);
    brdfBlue = new Lambertian(Color::COLOR_BLUE * 0.3);

    brdfWhite = new Lambertian(Color::COLOR_WHITE * 0.3);
    brdfYellow = new Lambertian(Color::COLOR_YELLOW * 0.3);

    brdfAqua = new Lambertian(Color::COLOR_AQUA * 0.3);
    brdfPurple = new Lambertian(Color::COLOR_PURPLE * 0.3);

    brdfMirror = new Mirror();
    brdfGlass = new Glass(1, 1.5);

    texture = new Checkboard();
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

Brdf *BrdfMgr::getPurpleBrdf()
{
    return brdfPurple;
}

Brdf *BrdfMgr::getMirrorBrdf()
{
    return brdfMirror;
}

Brdf *BrdfMgr::getGlassBrdf()
{
    return brdfGlass;
}

Checkboard *BrdfMgr::getTexture()
{
    return texture;
}
