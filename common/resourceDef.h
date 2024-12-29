#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>

class ResourceDef
{
public:
    inline const static std::string LENA = "../resource/lena.png";
    
    inline const static std::string COMPLEX_BUNNY = "../resource/bunny.obj";
    inline const static std::string SIMPLE_BUNNY = "../resource/simple_bunny.obj";
    inline const static std::string LOW_BUNNY = "../resource/low_bunny.obj";
    inline const static std::string TEAPOT = "../resource/teapot.obj";
    
    inline const static std::string BRDF_WHITE = "../resource/ilm_l3_37_matte_rgb.bsdf";
    inline const static std::string BRDF_GREEN = "../resource/acrylic_felt_green_rgb.bsdf";
    inline const static std::string BRDF_MINT = "../resource/chm_mint_rgb.bsdf";
    inline const static std::string BRDF_METAL = "../resource/ilm_l3_37_metallic_rgb.bsdf";
    inline const static std::string BRDF_TARKIN_TUNIC = "../resource/ilm_aniso_tarkin_tunic_rgb.bsdf";
    inline const static std::string BRDF_SARI_SILK = "../resource/aniso_sari_silk_2color_rgb.bsdf";
    inline const static std::string BRDF_BRUSHED_ALUMINIUM = "../resource/aniso_brushed_aluminium_1_rgb.bsdf";
    inline const static std::string BRDF_GREEN_PVC = "../resource/aniso_green_pvc_rgb.bsdf";
};

#endif