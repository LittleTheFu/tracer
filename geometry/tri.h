#ifndef _TRI_H_
#define _TRI_H_

#include "geometry.h"
#include "vector.h"
#include <memory>

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
        std::shared_ptr<Material> material);

    void set(const TriVertex &a,
                const TriVertex &b,
                const TriVertex &c,
                const Vector3 &pos,
                std::shared_ptr<Material> material);

    void getSplitChildren(Tri *outTri_1, Tri *outTri_2, Tri *outTri_3) const;

    virtual bool hit(const Ray &ray, HitRecord &record) const override;
    
    virtual Vector3 getCentroid() const override;
    virtual float surfaceArea() const override;
    virtual void buildBoundBox() override;
    virtual bool testHit(const Ray &localRay, float &t) const override;

private:
    bool isAllFacePositive(const Vector3 &p) const;
    void getWeight(const Vector3 &p, float &wa, float &wb, float &wc) const;
    void calcNormal();

    //can be optimized because both methodes called the func getWeight()
    Vector3 getWeightedNormal(const Vector3 &p) const;
    // void getWeightedUV(const Vector3 &p, float &u, float &v) const;

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