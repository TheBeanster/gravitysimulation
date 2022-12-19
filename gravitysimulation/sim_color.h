#pragma once

#include "sim_util.h"

typedef union
{
	unsigned int color;
	struct
	{
		unsigned char r, g, b, a;
	} rgba;
} color_t;



color_t color_from_hsv(
	double hue,
	double saturation,
	double value);



#define RADIANSTOANGLE(r) r * (360.0 / (3.1415*2.0))