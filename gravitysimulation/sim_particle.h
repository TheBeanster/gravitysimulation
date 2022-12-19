#pragma once

#include "sim_util.h"
#include "sim_color.h"



typedef struct
{
	double x;
	double y;
	double velx;
	double vely;
	color_t color;
} particle_t;



/// <summary>
/// Sets the data for the particle with the current build particle id
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="velx"></param>
/// <param name="vely"></param>
/// <returns></returns>
particle_t* create_particle(
	double x,
	double y,
	double velx,
	double vely,
	color_t color
);




particle_t* get_particle(int id);
