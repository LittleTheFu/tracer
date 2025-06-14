#ifndef _BXDF_TYPE_H_
#define _BXDF_TYPE_H_

enum BxdfType
{
    DIFFUSE = 1 << 0,
    MEASURED = 1 << 7,

    REFLECTION = 1 << 9,
    TRANSMISSION = 1 << 10,

    ALL = DIFFUSE | MEASURED,
};

#endif