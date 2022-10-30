#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
public:
    Color();
    Color(float r, float g, float b);

    float r, g, b;

    const static Color COLOR_BLACK;
    const static Color COLOR_WHITE;
    const static Color COLOR_RED;
    const static Color COLOR_GREEN;
    const static Color COLOR_BLUE;
};

#endif