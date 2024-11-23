#ifndef _MEDIA_H_
#define _MEDIA_H_

#include "color.h"

class Media
{
public:
    Media(float a, float s, Color e);
    Media();

public:
    float sigma_a;
    float sigma_s;
    float sigma_n;
    float sigma_major;

    Color emitColor;
};

#endif