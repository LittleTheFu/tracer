#include "vox.h"
#include <fstream>
#include <iostream>

Vox::Vox()
{
    m_data = std::make_unique<float[]>(NUM * NUM * NUM);

    std::ifstream ifs("../resource/grid.88.bin", std::ios::binary);

    ifs.read((char*)m_data.get(), sizeof(float) * NUM * NUM * NUM);
    ifs.close();

    // for(int i = 0; i < NUM * NUM * NUM; i++)
    //     std::cout << m_data[i] << std::endl;
}

float Vox::get(int x, int y, int z) const
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
    int xOffset = 50;
    int yOffset = 0;
    int zOffset = 0;

    // float scale = 0.8;
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
    
    x = (x % NUM + NUM) % NUM;
    y = (y % NUM + NUM) % NUM;
    z = (z % NUM + NUM) % NUM;

    return m_data[x + y * NUM + z * NUM * NUM];
}
