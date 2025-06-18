#include "simpleHitter.h"
#include "mathConstantDef.h"
#include "mathUtility.h"
#include <cassert>

Color SimperHitter::getColorFromLight(const Ray &ray) const
{
    float t = 0.0f;
    float dot = 1.0f;
    Vector3 normal;

    Interaction _interaction;
    if (!light_->getGeometryPrimitive()->getGeometry()->hit(ray, _interaction))
    {
        return Color::COLOR_BLACK;
    }

    Color color = light_->getColor();

    Interaction interaction;
    if (!hitGeometryObjectOnly(ray, interaction, light_->getGeometryPrimitive()))
    {
        return color;
    }

    if (_interaction.t < interaction.t)
    {
        return color;
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

    return hit;
}

bool SimperHitter::hitLightOnly(const Ray &ray, float &t, Vector3 &normal, float &dot) const
{
    
    Interaction interaction;
    bool hit = light_->getGeometryPrimitive()->getGeometry()->hit(ray, interaction);

    //no more used
    assert(0);
    return hit;
}