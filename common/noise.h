#ifndef _NOISE_H_
#define _NOISE_H_

#include "vector.h"

class Noise
{
public:
    Noise();
    float getValue(const Vector3 &v) const;
    float getValue(float u, float v) const;

private:
    int modIndex(int n) const;
    void getComponent(float a, int &i, float &f) const;
    
    const static int NUM = 16;
    Vector3 m_data[NUM][NUM][NUM];
};

#endif