#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>

class ResourceDef
{
public:
    inline const static std::string LENA = "../resource/lena.png";
    inline const static std::string BUNNY = "../resource/bunny.obj";
    inline const static std::string SIMPLE_BUNNY = "../resource/simple_bunny.obj";
    inline const static std::string LOW_BUNNY = "../resource/low_bunny.obj";
    inline const static std::string LOW_LOW_BUNNY = "../resource/low_low_bunny.obj";
    inline const static std::string TEAPOT = "../resource/teapot.obj";
    inline const static std::string TESTED_BRDF_WHITE = "../resource/ilm_l3_37_matte_rgb.bsdf";
    inline const static std::string TESTED_BRDF_GREEN = "../resource/acrylic_felt_green_rgb.bsdf";
    inline const static std::string TESTED_BRDF_MINT = "../resource/chm_mint_rgb.bsdf";
};

#endif