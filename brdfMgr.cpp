#include "brdfMgr.h"
#include "color.h"
#include <iostream>

BrdfMgr::BrdfMgr()
{
    brdf = new Lambertian(Color::COLOR_RED * 0.2);
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

Brdf* BrdfMgr::getBrdf()
{
    return brdf;
}