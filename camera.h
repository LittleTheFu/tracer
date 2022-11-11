#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "objectpool.h"
#include "vector.h"
#include "transform.h"

class Camera
{
public:
    Camera(const ObjectPool *pool);

    void build(const Vector3 &position, const Vector3 &direction, const Vector3 &up);
    void build(const Vector3 &position, const Vector3 &theta);

    Transform getTransform() const;
    
    void render();
    bool saveToImage() const;

private:
    const ObjectPool *m_pObjectPool;
    std::vector<unsigned char> m_Image;

    Transform m_transform;

    unsigned m_Width;
    unsigned m_Height;
    unsigned m_factor;

    int m_BounceTime;
};

#endif