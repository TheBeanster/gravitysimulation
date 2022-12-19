#pragma once

#include "sim_util.h"
#include "sim_particle.h"
#include "sim_object.h"



typedef struct
{
	double x;
	double y;
} trajectorypoint_t;

extern trajectorypoint_t* trajectory_points;
extern int trajectory_numpoints;
extern int trajectory_particleid;
extern particle_t* trajectory_particle;
extern int trajectory_curpoint;

void init_trajectory(int numiterations, int particleid);

void update_particle_trajectory();

void render_particle_trajectory();
