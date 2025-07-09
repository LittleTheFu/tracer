#ifndef _C_BALL_H_
#define _C_BALL_H_

#include <memory>

#include "geometry.h"

class Ball : public Geometry
{
public:
    Ball();
    Ball(const Vector3 &rotate, const Vector3 &position, float r);

    //for volume interaction
    bool hit(const Ray &ray, float &tMin, float &tMax) const;
    //end(for volume interaction)

    virtual bool hit(const Ray &ray, Interaction &interaction) const override;
    virtual Vector3 sampleFromPoint(const Vector3 &thatPoint, float &pdf, Vector3 &normal) const override;

    Vector3 getLocalDirection(float u, float v) const;

    virtual Vector3 getCentroid() const override;
    virtual float surfaceArea() const override;

    virtual void buildBoundBox() override;
    virtual bool testHit(const Ray &localRay, float &t) const override;

    bool isIn(const Vector3 &point) const;
    
public:
    float r;
    
private:
    virtual Vector3 dpdu(const Vector3 &point) const override;
    virtual Vector3 dpdv(const Vector3 &point) const override;

    virtual float u(const Vector3 &point) const override;
    virtual float v(const Vector3 &point) const override;

    Vector3 getLocalNormal(const Vector3 &point) const;
    Vector3 getLocalPoint(float theta, float phi) const;

    float getPhi(const Vector3 &point) const;
    float getTheta(const Vector3 &point) const;

private:
    bool getHitParam(float t_min, float t_max, float &t_out) const;
    void genRayHitParam(const Ray &ray, float &a_out, float &b_out, float &c_out) const;
};

#endif