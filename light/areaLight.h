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
    Vector3 sample(const Vector3 &thatPoint, float &pdf, Vector3 &normal) const;


    void setIntensity(float intensity);
    float getIntensity() const;

    void applyTransform(const Transform &t);

    std::shared_ptr<GeometryPrimitive> getGeometryPrimitive() const;
private:
    float intensity_;
    Color color_;
    std::shared_ptr<GeometryPrimitive> geometryPrimitive_;
};

#endif