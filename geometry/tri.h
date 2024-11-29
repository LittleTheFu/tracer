#ifndef _TRI_H_
#define _TRI_H_

#include "geometry.h"
#include "vector.h"

class TriVertex
{
public:
    TriVertex() {};
    TriVertex(float x, float y, float z) : pos(x, y, z) {}
    TriVertex(float x, float y, float z, float nx, float ny, float nz) : pos(x, y, z), normal(nx, ny, nz) {}
    TriVertex(const Vector3 &_pos, const Vector3 &_normal):pos(_pos),normal(_normal){}

public:
    void setUV(float _u, float _v)
    {
        u = _u;
        v = _v;
    }

    Vector3 pos;
    Vector3 normal;

    float u;
    float v;
};

class Tri : public Geometry
{
public:
    Tri();
    Tri(const TriVertex &a,
        const TriVertex &b,
        const TriVertex &c,
        const Vector3 &pos,
        const std::shared_ptr<const Material>& material);

    void set(const TriVertex &a,
                const TriVertex &b,
                const TriVertex &c,
                const Vector3 &pos,
                const std::shared_ptr<const Material>& material);

    void getSplitChildren(Tri *outTri_1, Tri *outTri_2, Tri *outTri_3) const;

    virtual bool hit(const Ray &ray, HitRecord &record) const override;
    
    virtual Vector3 getCentroid() const;
    virtual float surfaceArea() const override;
    virtual void buildBoundBox() override;

    Vector3 getLocalNormal(bool reverse = false) const;

private:
    bool isAllFacePositive(const Vector3 &p) const;
    void calcNormal();

private:
    virtual Vector3 dpdu(const Vector3 &point) const override;
    virtual Vector3 dpdv(const Vector3 &point) const override;

    virtual float u(const Vector3 &point) const override;
    virtual float v(const Vector3 &point) const override;

private:
    TriVertex m_a;
    TriVertex m_b;
    TriVertex m_c;

    Vector3 m_localCentroid;

    Vector3 m_ab;
    Vector3 m_bc;
    Vector3 m_ca;

    Vector3 m_normal;
    Vector3 m_pos;
};

#endif