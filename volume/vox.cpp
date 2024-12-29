#include <fstream>
#include <iostream>

#include "vox.h"

Vox::Vox()
{
    m_data = std::make_unique<float[]>(NUM * NUM * NUM);

    std::ifstream ifs("../resource/grid.88.bin", std::ios::binary);

    ifs.read((char*)m_data.get(), sizeof(float) * NUM * NUM * NUM);
    ifs.close();

    // for(int i = 0; i < NUM * NUM * NUM; i++)
    //     std::cout << m_data[i] << std::endl;
}

float Vox::get(float x, float y, float z) const
{
    // if (x >= NUM)
    //     return 0;
    // if (y >= NUM)
    //     return 0;
    // if (z >= NUM)
    //     return 0;

    // if (x < 0)
    //     return 0;
    // if (y < 0)
    //     return 0;
    // if (z < 0)
    //     return 0;

    //hardcode for test
    float xOffset = 0;
    float yOffset = 0;
    float zOffset = 0;

    // float scale = 0.99;
    // x *= scale;
    // y *= scale;
    // z *= scale;

    x += xOffset;
    y += yOffset;
    z += zOffset;

    // if (x >= NUM)
    //     return 0;
    // if (y >= NUM)
    //     return 0;
    // if (z >= NUM)
    //     return 0;

    // if (x < 0)
    //     return 0;
    // if (y < 0)
    //     return 0;
    // if (z < 0)
    //     return 0;
    int _x = (int)x;
    int _y = (int)y;
    int _z = (int)z;
    
    int fx = (_x % NUM + NUM) % NUM;
    int fy = (_y % NUM + NUM) % NUM;
    int fz = (_z % NUM + NUM) % NUM;

    return m_data[fx + fy * NUM + fz * NUM * NUM];
}
