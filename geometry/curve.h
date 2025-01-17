#ifndef _CURVE_H_
#define _CURVE_H_

#include <vector>

#include "geometry.h"
#include "vector.h"

class Curve : public Geometry
{
public:
    Curve(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const Vector3 &p3);

    void setWidth(float width);

    virtual bool hit(const Ray &ray, HitRecord &record) const override;
    virtual void buildBoundBox() override;

private:
    virtual Vector3 dpdu(const Vector3 &point) const override;
    virtual Vector3 dpdv(const Vector3 &point) const override;

    virtual float u(const Vector3 &point) const override;
    virtual float v(const Vector3 &point) const override;

private:
    bool hitRecursive(const Ray &ray,
                      HitRecord &record,
                      int depth,
                      float t0,
                      float t1) const;

    bool _hitRecursive(const Ray &ray,
                       int depth,
                       const std::vector<Vector3> &controlPoints) const;

    bool hitBoundBox(const Ray &ray,const std::vector<Vector3> &controlPoints) const;
    bool hitCurveSegment(const Ray &ray, const std::vector<Vector3> &controlPoints) const;

    void split(std::vector<Vector3> &left, std::vector<Vector3> &right) const;

private:
    static Vector3 getPoint(float u, const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const Vector3 &p3);

private:
    Vector3 m_p0;
    Vector3 m_p1;
    Vector3 m_p2;
    Vector3 m_p3;

    float m_width;

private:
    static const int CONTROL_POINTS_NUM;
    static const int MAX_DEPTH;
};

#endif