#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
public:
    float r, g, b;

public:
    Color();
    Color(float r, float g, float b);
    // Color(unsigned char r, unsigned char g, unsigned char b);
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