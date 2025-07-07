#include "simpleHitter.h"
#include "mathConstantDef.h"
#include "mathUtility.h"
#include <cassert>
#include "medium.h"


Color SimperHitter::getColorFromLight(const Ray &ray, int index) const
{
    if (index >= lights_.size())
    {
        return Color::COLOR_BLACK;
    }

    float t = 0.0f;
    float dot = 1.0f;
    Vector3 normal;

    Interaction _interaction;
    if (!lights_.at(index)->getGeometryPrimitive()->getGeometry()->hit(ray, _interaction))
    {
        return Color::COLOR_BLACK;
    }

    Color color = lights_.at(index)->getColor();

    Ray shadowRay(ray);
    float tr = 1.0f;
    while (true)
    {
        Interaction interaction;
        bool isHit = hitGeometryObjectOnly(shadowRay, interaction, nullptr);

        // no other object hit, return light color directly
        if (interaction.primitive == lights_.at(index)->getGeometryPrimitive())
            return tr * color;

        if (interaction.is_volume_boundary_hit)
        {
            if (shadowRay.medium)
            {
                tr *= shadowRay.medium->transmittance(shadowRay, interaction.t);

                shadowRay.medium = nullptr;
                shadowRay.origin = interaction.point + shadowRay.dir * MathConstant::FLOAT_SMALL_NUMBER;
            }
            else
            {
                shadowRay.medium = interaction.medium;
                shadowRay.origin = interaction.point + shadowRay.dir * MathConstant::FLOAT_SMALL_NUMBER;
            }
        }
        else
        {
            return Color::COLOR_BLACK;
        }

        // if (_interaction.t < interaction.t)
        // {
        //     return color;
        // }
    }

    return Color::COLOR_BLACK;
}

bool SimperHitter::hitGeometryObjectOnly(const Ray &ray,
                                         Interaction &interaction,
                                         std::shared_ptr<Primitive> skipPrimitive) const
{
    bool hit = false;
    float tMin = MathConstant::FLOAT_MAX;

    // for (auto it = m_objects.begin(); it != m_objects.end(); it++)
    for (auto it = primitives_.begin(); it != primitives_.end(); it++)
    {
        if ((*it) == skipPrimitive)
        {
            continue;
        }

        Interaction tempInteraction;
        if ((*it)->getGeometry()->hit(ray, tempInteraction))
        {
            if (tempInteraction.t < tMin)
            {
                tMin = tempInteraction.t;
                interaction = tempInteraction;
                interaction.primitive = (*it);
                hit = true;
            }
        }
    }

    // quick and dirty
    if (hit)
    {
        if (isVolumePrimitive(interaction.primitive))
        {
            interaction.is_volume_boundary_hit = true;
            interaction.is_surface_hit = false;
            interaction.medium = volume_->getMedium();
            interaction.mediumBoundary = interaction.primitive->getMediumBoundary();
        }
        else
        {
            interaction.is_volume_boundary_hit = false;
            interaction.is_surface_hit = true;
            interaction.medium = nullptr;
            interaction.mediumBoundary = interaction.primitive->getMediumBoundary();
        }
    }
    else
    {
        interaction.is_volume_boundary_hit = false;
        interaction.is_surface_hit = false;
        interaction.medium = nullptr;
    }

    return hit;
}

// bool SimperHitter::hitLightOnly(const Ray &ray, float &t, Vector3 &normal, float &dot) const
// {

//     Interaction interaction;
//     bool hit = light_->getGeometryPrimitive()->getGeometry()->hit(ray, interaction);

//     //no more used
//     assert(0);
//     return hit;
// }