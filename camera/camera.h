#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <memory>
#include <string>

#include "objectpool.h"
#include "ray.h"
#include "tracer.h"
#include "transform.h"
#include "vector.h"

class Camera
{
public:
    Camera(std::shared_ptr<Tracer> tracer, int resolutionScale, int samplersPerPixel);

    void setPool(std::shared_ptr<const ObjectPool> pool);

    void build(const Vector3 &position, const Vector3 &direction, const Vector3 &up);
    void build(const Vector3 &position, const Vector3 &theta);

    Transform getTransform() const;

    void enableLog();
    void disableLog();

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
    int m_resolutionScale;
    int m_samplersPerPixel;

    bool m_enableLog;

private:
    const static int default_screen_width;
    const static int default_screen_height;

protected:
    unsigned m_Width;
    unsigned m_Height;
};

#endif