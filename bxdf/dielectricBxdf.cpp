#include "dielectricBxdf.h"
#include <mathUtility.h>
#include <cassert>

DielectricBxdf::DielectricBxdf(float etaI, float etaT)
    : Bxdf(static_cast<BxdfType>(BxdfType::SPECULAR | BxdfType::REFLECTION | BxdfType::TRANSMISSION))
{
    etaI_ = etaI;
    etaT_ = etaT;
}

Color DielectricBxdf::f(const Vector3 &wo, const Vector3 &wi) const
{
    return Color::COLOR_BLACK;
}

float DielectricBxdf::pdf(const Vector3 &wo, const Vector3 &wi) const
{
    return 0.0f;
}

Color DielectricBxdf::sample_f(const Vector3 &wo, Vector3 &wi, float &pdf, const Interaction &interaction) const
{
    Vector3 normal = Vector3(0, 0, 1);
    float dot = wo * normal;

    float etaI = etaI_;
    float etaT = etaT_;

    if (dot < 0)
    {
        // normal = -normal;
        // std::swap(etaI, etaT);
    }

    // Vector3 inputVector = Vector3(wo.x, wo.y, -wo.z);
    Vector3 inputVector = -wo;
    bool totalReflect;
    float fresnel;
    wi = inputVector.refract(normal, etaI, etaT, totalReflect, fresnel);

    assert(MathUtility::is_in_range(fresnel, 0.0f, 1 + 0.00001f, true, true));
    
    pdf = fresnel;

    static int totalReflectCnt = 0;
    static int totalTransmitCnt = 0;

    if(totalReflectCnt % 100 == 0)
    {
        std::cout << "totalReflectCnt: " << totalReflectCnt << std::endl;
        std::cout << "totalTransmitCnt: " << totalTransmitCnt << std::endl;
    }


    //for debug
    if(totalReflect)
    {
        totalReflectCnt++;
        return Color::COLOR_WHITE;
    }
    else
    {
        totalTransmitCnt++;
        // return Color::COLOR_WHITE;
    }
    // static int moreThanOneCnt = 0;
    // static int lessThanOneCnt = 0;

    // if(etaI > etaT)
    // {
    //     moreThanOneCnt++;
    // }
    // else
    // {
    //     lessThanOneCnt++;
    // }

    // if(moreThanOneCnt % 10 == 0)
    // {
    //     std::cout << "moreThanOneCnt: " << moreThanOneCnt << std::endl;
    //     std::cout << "lessThanOneCnt: " << lessThanOneCnt << std::endl;
    // }

    return Color::COLOR_WHITE * MathUtility::sq(etaI / etaT);
    // return Color::COLOR_WHITE;
}
