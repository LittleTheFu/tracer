#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "objectpool.h"

class Camera
{
public:
    Camera(const ObjectPool *pool);

    void render();
    bool saveToImage();

private:
    const ObjectPool *m_pObjectPool;
    std::vector<unsigned char> m_Image;

    unsigned m_Width;
    unsigned m_Height;
    unsigned m_factor;

    int m_BounceTime;
};

#endif