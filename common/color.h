#ifndef _COLOR_H_
#define _COLOR_H_

#include <iostream>

class Color
{
public:
    float r, g, b;

public:
    Color();
    Color(float r, float g, float b);

    float getClampedMaxComponent() const;
    
    bool isValid() const;
    void getConvertedValue(unsigned char &r, unsigned char &g, unsigned char &b) const;

    int validOverflow(float m = 1.0f) const;
    Color &clamp();

    Color &operator+=(const Color &that);
    Color &operator*=(const Color &that);
    Color operator*(const float m) const;
    Color operator*(const Color &that) const;
    Color operator/(const float m) const;
    Color &operator/=(const float m);

    bool operator==(const Color that) const;
    bool operator!=(const Color that) const;

    friend std::ostream &operator<<(std::ostream &os, const Color &color);

    const static Color COLOR_BLACK;
    const static Color COLOR_WHITE;
    const static Color COLOR_RED;
    const static Color COLOR_GREEN;
    const static Color COLOR_BLUE;
    const static Color COLOR_AQUA;
    const static Color COLOR_YELLOW;
    const static Color COLOR_PURPLE;
    const static Color COLOR_CYAN;
    const static Color COLOR_MAGENTA;
    const static Color COLOR_ORANGE;
    const static Color COLOR_GRAY;
    const static Color COLOR_LIGHT_GRAY;
    const static Color COLOR_DARK_GRAY;
    const static Color COLOR_BROWN;
    const static Color COLOR_PINK;
    const static Color COLOR_LIME;
    const static Color COLOR_TEAL;
    const static Color COLOR_NAVY;
    const static Color COLOR_SILVER;
    const static Color COLOR_GOLD;
    const static Color COLOR_INDIGO;
    const static Color COLOR_TURQUOISE;
};

#endif