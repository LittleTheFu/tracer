#ifndef _MATERIAL_H_
#define _MATERIAL_H_

class Material
{
public:
    Material();
    Material(unsigned char r, unsigned char g, unsigned char b);

    void set(unsigned char r, unsigned char g, unsigned char b);

    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    const static Material MTRL_RED;
    const static Material MTRL_GREEN;
    const static Material MTRL_BLUE;
    const static Material MTRL_YELLOW;
    const static Material MTRL_AQUA;
    const static Material MTRL_SILVER;
    const static Material MTRL_GRAY;
    const static Material MTRL_PURPLE;
    const static Material MTRL_WHITE;
    const static Material MTRL_BLACK;
};

#endif