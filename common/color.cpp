#include "color.h"
#include <cassert>
#include "common.h"
#include "mathUtility.h"

const Color Color::COLOR_BLACK = Color(0, 0, 0);
const Color Color::COLOR_WHITE = Color(1, 1, 1);
const Color Color::COLOR_RED = Color(1, 0, 0);
const Color Color::COLOR_GREEN = Color(0, 1, 0);
const Color Color::COLOR_BLUE = Color(0, 0, 1);
const Color Color::COLOR_AQUA = Color(0, 1, 1);
const Color Color::COLOR_YELLOW = Color(1, 1, 0);
const Color Color::COLOR_PURPLE = Color(0.5, 0, 0.5);
const Color Color::COLOR_CYAN = Color(0, 1, 1);
const Color Color::COLOR_MAGENTA = Color(1, 0, 1);
const Color Color::COLOR_ORANGE = Color(1, 0.5, 0);
const Color Color::COLOR_GRAY = Color(0.5, 0.5, 0.5);
const Color Color::COLOR_LIGHT_GRAY = Color(0.75, 0.75, 0.75);
const Color Color::COLOR_DARK_GRAY = Color(0.25, 0.25, 0.25);
const Color Color::COLOR_BROWN = Color(0.647, 0.165, 0.165);
const Color Color::COLOR_PINK = Color(1, 0.753, 0.796);
const Color Color::COLOR_LIME = Color(0, 1, 0);
const Color Color::COLOR_TEAL = Color(0, 0.5, 0.5);
const Color Color::COLOR_NAVY = Color(0, 0, 0.5);
const Color Color::COLOR_SILVER = Color(0.753, 0.753, 0.753);
const Color Color::COLOR_GOLD = Color(1, 0.843, 0);
const Color Color::COLOR_INDIGO = Color(0.294, 0, 0.509);
const Color Color::COLOR_TURQUOISE = Color(0.251, 0.878, 0.816);

const Color Color::COLOR_LIGHT = Color(1, 1, 1);


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

bool Color::isValid() const
{
    float low = 0.0f;
    float high = 1.0f;

    bool bR = MathUtility::is_in_range(this->r, low, high, true, true);
    bool bG = MathUtility::is_in_range(this->g, low, high, true, true);
    bool bB = MathUtility::is_in_range(this->b, low, high, true, true);

    return (bR && bG && bB);
}

void Color::getConvertedValue(unsigned char &r, unsigned char &g, unsigned char &b) const
{
    const float MAX = 255;

    //does assert needed here? think about it later...

    float rr = MathUtility::clamp(this->r, 0, 1);
    float gg = MathUtility::clamp(this->g, 0, 1);
    float bb = MathUtility::clamp(this->b, 0, 1);

    r = static_cast<unsigned char>(rr * MAX);
    g = static_cast<unsigned char>(gg * MAX);
    b = static_cast<unsigned char>(bb * MAX);
}

int Color::validOverflow(float m) const
{
    int result = 0;

    if( r > m) result |= 1;
    if( g > m) result |= 2;
    if( b > m) result |= 4;

    return result;
}

Color &Color::clamp()
{
    r = MathUtility::clamp(r, 0, 1);
    g = MathUtility::clamp(g, 0, 1);
    b = MathUtility::clamp(b, 0, 1);

    return *this;
}

Color &Color::operator+=(const Color &that)
{
    // assert(that.r >= 0);
    // assert(that.g >= 0);
    // assert(that.b >= 0);

    r += that.r;
    g += that.g;
    b += that.b;

    // MathUtility::clamp(r, 0, 1);
    // MathUtility::clamp(g, 0, 1);
    // MathUtility::clamp(b, 0, 1);

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

    // float r = MathUtility::clamp(this->r * that.r, 0, 1);
    // float g = MathUtility::clamp(this->g * that.g, 0, 1);
    // float b = MathUtility::clamp(this->b * that.b, 0, 1);

    return Color(r, g, b);
}

Color Color::operator/(const float m) const
{
    // assert(m > 0);

    // float r = MathUtility::clamp(this->r / m, 0, 1);
    // float g = MathUtility::clamp(this->g / m, 0, 1);
    // float b = MathUtility::clamp(this->b / m, 0, 1);
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
    if (!MathUtility::is_float_equal(this->r, that.r))
    {
        return false;
    }

    if (!MathUtility::is_float_equal(this->g, that.g))
    {
        return false;
    }

    if (!MathUtility::is_float_equal(this->b, that.b))
    {
        return false;
    }

    return true;
}

bool Color::operator!=(const Color that) const
{
    return !(this->operator==(that));
}

std::ostream &operator<<(std::ostream &os, const Color &color)
{
    os << "( " << color.r << ", " << color.g << ", " << color.b << " )";

    return os;
}
