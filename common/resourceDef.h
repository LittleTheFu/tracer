#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>

class ResourceDef
{
public:
    inline const static std::string RES_FOLDER = "../resource/";
    
    inline const static std::string LENA = RES_FOLDER + "lena.png";
    inline const static std::string NORMAL = RES_FOLDER + "normal.png";
    
    inline const static std::string COMPLEX_BUNNY = RES_FOLDER + "bunny.obj";
    inline const static std::string SIMPLE_BUNNY = RES_FOLDER + "simple_bunny.obj";
    inline const static std::string LOW_BUNNY = RES_FOLDER + "low_bunny.obj";
    inline const static std::string TEAPOT = RES_FOLDER + "teapot.obj";
    inline const static std::string BOT = RES_FOLDER + "bot.fbx";
    inline const static std::string CUBE = RES_FOLDER + "cube.obj";
    inline const static std::string SLAB = RES_FOLDER + "slab.obj";
    inline const static std::string ROOM = RES_FOLDER + "wall.fbx";
    inline const static std::string WHITE_ROOM = RES_FOLDER + "whiteWall.fbx";
    inline const static std::string LEFT_WHITE_ROOM = RES_FOLDER + "leftWhiteWall.fbx";
    
    inline const static std::string BRDF_WHITE = RES_FOLDER + "ilm_l3_37_matte_rgb.bsdf";
    inline const static std::string BRDF_GREEN = RES_FOLDER + "acrylic_felt_green_rgb.bsdf";
    inline const static std::string BRDF_MINT = RES_FOLDER + "chm_mint_rgb.bsdf";
    inline const static std::string BRDF_METAL = RES_FOLDER + "ilm_l3_37_metallic_rgb.bsdf";
    inline const static std::string BRDF_TARKIN_TUNIC = RES_FOLDER + "ilm_aniso_tarkin_tunic_rgb.bsdf";
    inline const static std::string BRDF_SARI_SILK = RES_FOLDER + "aniso_sari_silk_2color_rgb.bsdf";
    inline const static std::string BRDF_BRUSHED_ALUMINIUM = RES_FOLDER + "aniso_brushed_aluminium_1_rgb.bsdf";
    inline const static std::string BRDF_GREEN_PVC = RES_FOLDER + "aniso_green_pvc_rgb.bsdf";
};

#endif