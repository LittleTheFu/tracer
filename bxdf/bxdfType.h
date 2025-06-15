#ifndef _BXDF_TYPE_H_
#define _BXDF_TYPE_H_

enum class BxdfType : unsigned int
{
    NONE = 0,
    DIFFUSE = 1 << 0,
    GLOSSY = 1 << 1,
    SPECULAR = 1 << 2,

    REFLECTION = 1 << 3,
    TRANSMISSION = 1 << 4,

    MEASURED = 1 << 7,

    ALL = DIFFUSE | GLOSSY | SPECULAR | REFLECTION | TRANSMISSION | MEASURED,
    ALL_REFLECTION = REFLECTION | DIFFUSE | GLOSSY | SPECULAR,
    ALL_TRANSMISSION = TRANSMISSION | GLOSSY | SPECULAR,
};

inline BxdfType operator|(BxdfType a, BxdfType b)
{
    return static_cast<BxdfType>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline BxdfType operator&(BxdfType a, BxdfType b)
{
    return static_cast<BxdfType>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}

inline BxdfType operator^(BxdfType a, BxdfType b)
{
    return static_cast<BxdfType>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b));
}

inline BxdfType operator~(BxdfType a)
{
    return static_cast<BxdfType>(~static_cast<unsigned int>(a));
}

inline bool hasFlag(BxdfType type, BxdfType flag)
{
    return static_cast<unsigned int>(type & flag) != 0;
}

#endif