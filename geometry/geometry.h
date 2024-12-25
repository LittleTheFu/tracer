#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "ray.h"
#include "hitrecord.h"
#include "vector.h"
#include "transform.h"
#include "boundBox.h"
#include "tagDef.h"
#include "media.h"
#include <memory>


class Geometry
{
public:
    Media m_outsideMedia;
    Media m_insideMedia;  
      
public:
    Geometry();
    
    void init(const Vector3 &rotate, const Vector3 &position);
    void setPosition(const Vector3 &position);
    Vector3 getPosition() const;

    Vector3 getLocalPosition(const Vector3 &worldPosition) const;

    virtual bool hit(const Ray &ray, HitRecord &record) const = 0;
    virtual Vector3 sampleFromPoint(const Vector3 &thatPoint, float &pdf) const;
    virtual Color get_f(const Vector3 &wo, const Vector3 &wi, const Vector3 &point, const Vector3 &normal) const;
    
    virtual Vector3 getCentroid() const;
    virtual float surfaceArea() const;
    
    //what we need is the boundBox built from tranformed points
    virtual void buildBoundBox();
    BoundBox getBoundBox() const;

    void applyTransform(const Transform &t);
    void setTransform(const Transform &t);
    Transform getTransform() const;

    void setMaterial(std::shared_ptr<Material> pMtrl);
    bool isVolume() const;

//for development
public:
    void setTag(Tag tag);
    Tag getTag() const;

    std::string getClassName() const;

private:
    virtual Vector3 dpdu(const Vector3 &point) const = 0;
    virtual Vector3 dpdv(const Vector3 &point) const = 0;

    virtual float u(const Vector3 &point) const = 0;
    virtual float v(const Vector3 &point) const = 0;

protected:
    Transform m_transform;
    Tag m_tag;

    BoundBox m_boundBox;

    std::shared_ptr<Material> m_pMtrl;
};

#endif