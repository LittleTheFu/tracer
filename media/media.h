#ifndef _MEDIA_H_
#define _MEDIA_H_

#include "color.h"

class Media
{
public:
    Media(float a, float s, Color e)
    : sigma_a(a), sigma_s(s), sigma_n(0.2f), emitColor(e)
    {
        sigma_major = sigma_s + sigma_a + sigma_n;
    }

    Media():Media(0.6f,0.4f,Color::COLOR_YELLOW) {}

public:
    float sigma_a;
    float sigma_s;
    float sigma_n;
    float sigma_major;

    Color emitColor;
};

#endif