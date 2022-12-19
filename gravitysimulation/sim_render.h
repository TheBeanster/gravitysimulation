#pragma once

#include "sim_util.h"



typedef enum
{
	RENDER_OBJECTS,
	RENDER_PARTICLES,
	// And so on...
} render_flags_t;



extern double cam_sinr;
extern double cam_cosr;

void render_simulation();

void render_point_in_world(double x, double y);
