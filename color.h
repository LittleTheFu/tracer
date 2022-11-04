#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
public:
    Color();
    Color(float r, float g, float b);

    void getConvertedValue(unsigned char &r, unsigned char &g, unsigned char &b);

    float r, g, b;

    Color &operator+=(const Color &that);
    Color operator*(const float m) const;
    Color operator*(const Color &that) const;
    Color operator/(const float m) const;

    bool operator==(const Color that) const;
    bool operator!=(const Color that) const;

    const static Color COLOR_BLACK;
    const static Color COLOR_WHITE;
    const static Color COLOR_RED;
    const static Color COLOR_GREEN;
    const static Color COLOR_BLUE;
    const static Color COLOR_AQUA;
    const static Color COLOR_YELLOW;
    const static Color COLOR_PURPLE;
};

#endif