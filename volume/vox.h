#ifndef _VOX_H_
#define _VOX_H_

#include <memory>

class Vox
{
public:
    static const int NUM = 128;
public:
    Vox();

    float get(int x, int y, int z) const;

    std::unique_ptr<float[]> m_data;
};

#endif
