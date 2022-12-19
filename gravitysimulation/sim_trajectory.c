#include "sim_trajectory.h"

#include "sim_render.h"
#include "system.h"
#include <SDL.h>

trajectorypoint_t*	trajectory_points		= 0;
int					trajectory_particleid	= 0;
int					trajectory_numpoints	= 0;
particle_t*			trajectory_particle		= 0;
int					trajectory_curpoint		= 0;



void init_trajectory(int numiterations, int particleid)
{
	trajectory_particleid = particleid;
	trajectory_particle = get_particle(particleid);
	
	trajectory_numpoints = numiterations;
	trajectory_points = mem_alloc(sizeof(trajectorypoint_t) * numiterations);

	trajectory_curpoint = 0;
}

void update_particle_trajectory()
{
	trajectory_points[trajectory_curpoint].x = trajectory_particle->x;
	trajectory_points[trajectory_curpoint].y = trajectory_particle->y;

	trajectory_curpoint++;

	if (trajectory_curpoint >= trajectory_numpoints)
		trajectory_curpoint = 0;
}

void render_particle_trajectory()
{
	SDL_SetRenderDrawColor(main_renderer, 255, 255, 255, 255);
	for (int i = 0; i < trajectory_numpoints; i++)
	{
		render_point_in_world(
			trajectory_points[i].x, 
			trajectory_points[i].y);
	}
}
