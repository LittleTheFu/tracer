#ifndef _MEDIA_H_
#define _MEDIA_H_

#include "color.h"

class Media
{
public:
    Media(float a, float s, Color e);
    Media();

    void set(float a, float s, float n, Color e);
    void clear();

    bool isClear() const;

public:
    float sigma_a;
    float sigma_s;
    float sigma_n;
    float sigma_major;

    Color emitColor;

private:
    bool m_isClear;
};

#endif