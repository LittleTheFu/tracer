#include "converter.h"

powitacq_rgb::Vector3f ThirdInterfaceConverter::toPowitVec(const Vector3 &vec)
{
    return powitacq_rgb::Vector3f(vec.x, vec.y, vec.z);
}

Vector3 ThirdInterfaceConverter::toVec(const powitacq_rgb::Vector3f &vec)
{
    return Vector3(vec.x(), vec.y(), vec.z());
}

Color ThirdInterfaceConverter::toColor(const powitacq_rgb::Vector3f &vec)
{
    return Color(vec.x(), vec.y(), vec.z());
}

powitacq_rgb::Vector3f ThirdInterfaceConverter::toPowitVec(const Color &color)
{
    return powitacq_rgb::Vector3f(color.r, color.g, color.b);
}
