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
    Vector3 local_surface_normal = Vector3(0, 0, 1); 
    if(!local_surface_normal.isSameDir(wo))
    {
        local_surface_normal = -local_surface_normal;
    }
    
    Vector3 inputVector = -wo;

    bool totalReflect;
    float fresnel;

    Vector3 temp_refracted_wi_local = inputVector.refract(local_surface_normal, 
                                                           etaI_, 
                                                           etaT_, 
                                                           totalReflect, 
                                                           fresnel);

    // assert(MathUtility::is_in_range(fresnel, 0.0f, 1.0f + 1e-5f, true, true)); 

    const float MIN_PROBABILITY_THRESHOLD = 1e-6f; 

    if (totalReflect) {
        // assert(0);
        wi = inputVector.reflect(local_surface_normal);
        
        pdf = 1.0f; 

        return Color::COLOR_WHITE;
    }
    else {
        float rand_val = MathUtility::genRandomDecimal();

        if (rand_val < fresnel) {
            // assert(0);
            wi = inputVector.reflect(local_surface_normal);
            pdf = std::max(MIN_PROBABILITY_THRESHOLD, fresnel); 
            
            return Color::COLOR_WHITE * (fresnel / pdf);
        } else {
            wi = temp_refracted_wi_local; 
            
            float transmittance_prob = 1.0f - fresnel;
            pdf = std::max(MIN_PROBABILITY_THRESHOLD, transmittance_prob); 
            
            Vector3 diff = wi + wo;
            // assert(MathUtility::is_in_range(diff.length(), 0.0f, 1.0f + 1e-5f, true, true));
            return Color::COLOR_WHITE * (transmittance_prob / pdf) * MathUtility::sq(etaI_ / etaT_);
        }
    }
}