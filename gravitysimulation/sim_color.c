#include "sim_color.h"

#include <math.h>



color_t color_from_hsv(
	double hue,
	double saturation,
	double value)
{
    color_t resultcolor;

    double C = saturation * value;
    double X = C * (1.0 - fabs(fmod(hue / 60.0, 2.0) - 1.0));
    double m = value - C;
    double r, g, b;

    if (hue >= 0 && hue < 60)
    {
        r = C, g = X, b = 0;
    } else if (hue >= 60 && hue < 120)
    {
        r = X, g = C, b = 0;
    } else if (hue >= 120 && hue < 180)
    {
        r = 0, g = C, b = X;
    } else if (hue >= 180 && hue < 240)
    {
        r = 0, g = X, b = C;
    } else if (hue >= 240 && hue < 300)
    {
        r = X, g = 0, b = C;
    } else
    {
        r = C, g = 0, b = X;
    }

    resultcolor.rgba.r = (unsigned char)((r + m) * 255.0);
    resultcolor.rgba.g = (unsigned char)((g + m) * 255.0);
    resultcolor.rgba.b = (unsigned char)((b + m) * 255.0);
    return resultcolor;
}
