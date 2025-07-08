#ifndef _AREA_LIGHT_H_
#define _AREA_LIGHT_H_

#include "geometry.h"
#include "transform.h"
#include "geometryPrimitive.h"


class AreaLight
{
public:
    AreaLight(std::shared_ptr<GeometryPrimitive> geometryPrimitive);
    ~AreaLight() = default;

    Color getColor() const;
    void setColor(const Color &finalColor);

    Vector3 sample(const Vector3 &thatPoint, float &pdf, Vector3 &normal) const;
    std::shared_ptr<GeometryPrimitive> getGeometryPrimitive() const;

    void applyIntensityScale(float scale);
    void applyTransform(const Transform &t);

private:
    Color color_;
    std::shared_ptr<GeometryPrimitive> geometryPrimitive_;
};

#endif