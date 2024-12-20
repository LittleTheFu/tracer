#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "objectpool.h"
#include "vector.h"
#include "transform.h"
#include <string>
#include "ray.h"
#include "tracer.h"
#include <memory>

class Camera
{
public:
    Camera(std::shared_ptr<Tracer> tracer);

    void setPool(std::shared_ptr<const ObjectPool> pool);

    void build(const Vector3 &position, const Vector3 &direction, const Vector3 &up);
    void build(const Vector3 &position, const Vector3 &theta);

    Transform getTransform() const;

    void setBounceTime(int bounceTime);

    void render();
    bool saveToImage(const std::string &name) const;

private:
    virtual Ray generateRay(float screenX, float screenY) const = 0;

private:
    void setImage(unsigned int x, unsigned int y, const Color &color);
    HitRecord InitHitRecord() const;
    void logProgress(unsigned int x, unsigned int y) const;

private:
    std::shared_ptr<const ObjectPool> m_pObjectPool;
    std::shared_ptr<const Tracer> m_pTracer;
    std::vector<unsigned char> m_Image;

    Transform m_transform;
    unsigned m_factor;
    int m_BounceTime;

private:
    const static int default_screen_width;
    const static int default_screen_height;

protected:
    unsigned m_Width;
    unsigned m_Height;
};

#endif