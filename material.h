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

    const static Material MTRL_1;
    const static Material MTRL_2;
    const static Material MTRL_3;
    const static Material MTRL_4;
    const static Material MTRL_5;
    const static Material MTRL_6;
    const static Material MTRL_7;
    const static Material MTRL_8;
    const static Material MTRL_9;
    const static Material MTRL_10;
};

#endif