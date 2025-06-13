#include "simpleHitter.h"
#include "mathConstantDef.h"
#include "mathUtility.h"

Color SimperHitter::getColorFromLight(const Ray &ray) const
{
    float t = 0.0f;
    float dot = 1.0f;
    Vector3 normal;

    if (!hitLightOnly(ray, t, normal, dot))
    {
        return Color::COLOR_BLACK;
    }

    Color color = light_->getColor() * light_->getIntensity();

    Interaction interaction;
    if (!hitGeometryObjectOnly(ray, interaction))
    {
        return color;
    }

    if (t < interaction.t)
    {
        return color;
    }

    return Color::COLOR_BLACK;
}

bool SimperHitter::hitGeometryObjectOnly(const Ray &ray, Interaction &interaction) const
{
    bool hit = false;
    float tMin = MathConstant::FLOAT_MAX;

    // for (auto it = m_objects.begin(); it != m_objects.end(); it++)
    for (auto it = primitives_.begin(); it != primitives_.end(); it++)
    {
        Interaction tempInteraction;
        if ((*it)->getGeometry()->hit(ray, tempInteraction))
        {
            if (tempInteraction.t < tMin)
            {
                tMin = tempInteraction.t;
                interaction = tempInteraction;
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

    return hit;
}