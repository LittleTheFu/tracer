#include "color.h"

const Color Color::COLOR_BLACK = Color(0, 0, 0);
const Color Color::COLOR_WHITE = Color(1, 1, 1);
const Color Color::COLOR_RED = Color(1, 0, 0);
const Color Color::COLOR_GREEN = Color(0, 1, 0);
const Color Color::COLOR_BLUE = Color(0, 0, 1);

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

void Color::getConvertedValue(unsigned char &r, unsigned char &g, unsigned char &b)
{
    const unsigned char MAX = 255;

    r = this->r * MAX;
    g = this->g * MAX;
    b = this->b * MAX;
}

Color Color::operator*(const float m) const
{
    const float r = this->r * m;
    const float g = this->g * m;
    const float b = this->b * m;

    return Color(r, g, b);
}
