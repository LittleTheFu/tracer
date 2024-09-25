#include "color.h"
#include <cassert>
#include "common.h"

const Color Color::COLOR_BLACK = Color(0, 0, 0);
const Color Color::COLOR_WHITE = Color(1, 1, 1);
const Color Color::COLOR_RED = Color(1, 0, 0);
const Color Color::COLOR_GREEN = Color(0, 1, 0);
const Color Color::COLOR_BLUE = Color(0, 0, 1);
const Color Color::COLOR_AQUA = Color(0, 1, 1);
const Color Color::COLOR_YELLOW = Color(1, 1, 0);
const Color Color::COLOR_PURPLE = Color(0.5, 0, 0.5);

Color::Color()
{
    this->r = 1;
    this->g = 1;
    this->b = 1;
}

Color::Color(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

// Color::Color(unsigned char r, unsigned char g, unsigned char b)
// {
//     const float MAX = 255;

//     this->r = r / MAX;
//     this->g = r / MAX;
//     this->b = r / MAX;
// }

void Color::getConvertedValue(unsigned char &r, unsigned char &g, unsigned char &b) const
{
    const unsigned char MAX = 255;

    float rr = Common::clamp(this->r, 0, 1);
    float gg = Common::clamp(this->g, 0, 1);
    float bb = Common::clamp(this->b, 0, 1);

    r = rr * MAX;
    g = gg * MAX;
    b = bb * MAX;
}

Color &Color::operator+=(const Color &that)
{
    // assert(that.r >= 0);
    // assert(that.g >= 0);
    // assert(that.b >= 0);

    r += that.r;
    g += that.g;
    b += that.b;

    // Common::clamp(r, 0, 1);
    // Common::clamp(g, 0, 1);
    // Common::clamp(b, 0, 1);

    return *this;
}

Color &Color::operator*=(const Color &that)
{
    r *= that.r;
    r *= that.g;
    r *= that.b;

    return *this;
}

Color Color::operator*(const float m) const
{
    const float r = this->r * m;
    const float g = this->g * m;
    const float b = this->b * m;

    return Color(r, g, b);
}

Color Color::operator*(const Color &that) const
{
    // assert(that.r >= 0);
    // assert(that.g >= 0);
    // assert(that.b >= 0);

    float r = this->r * that.r;
    float g = this->g * that.g;
    float b = this->b * that.b;

    // float r = Common::clamp(this->r * that.r, 0, 1);
    // float g = Common::clamp(this->g * that.g, 0, 1);
    // float b = Common::clamp(this->b * that.b, 0, 1);

    return Color(r, g, b);
}

Color Color::operator/(const float m) const
{
    // assert(m > 0);

    // float r = Common::clamp(this->r / m, 0, 1);
    // float g = Common::clamp(this->g / m, 0, 1);
    // float b = Common::clamp(this->b / m, 0, 1);
    float r = this->r / m;
    float g = this->g / m;
    float b = this->b / m;

    return Color(r, g, b);
}

Color &Color::operator/=(const float m)
{
    r /= m;
    g /= m;
    b /= m;

    return *this;
}

bool Color::operator==(const Color that) const
{
    if (!Common::is_float_equal(this->r, r))
    {
        return false;
    }

    if (!Common::is_float_equal(this->g, g))
    {
        return false;
    }

    if (!Common::is_float_equal(this->b, b))
    {
        return false;
    }

    return true;
}

bool Color::operator!=(const Color that) const
{
    return !this->operator==(that);
}