#ifndef _CONVERTER_H_
#define _CONVERTER_H_

#include <powitacq/powitacq_rgb.h>

#include "color.h"
#include "vector.h"

class ThirdInterfaceConverter
{
public:
    static powitacq_rgb::Vector3f toPowitVec(const Vector3 &vec);
    static Vector3 toVec(const powitacq_rgb::Vector3f &vec);

    static Color toColor(const powitacq_rgb::Vector3f &vec);
    static powitacq_rgb::Vector3f toPowitVec(const Color &color);
};

#endif