#include "brdfMgr.h"
#include "color.h"

BrdfMgr::BrdfMgr()
{
    brdf = new Lambertian(Color::COLOR_RED * 0.2);
}

Brdf* BrdfMgr::getBrdf()
{
    return brdf;
}