#include "sim_particle.h"

#include "sim_system.h"
#include "sim_world.h"



particle_t* create_particle(
	double x,
	double y,
	double velx,
	double vely,
	color_t color
)
{

	if (system_current_build_particleid >= system_particlecount) return 0;

	particle_t* p = &sim_particles[system_current_build_particleid];
	p->x = x;
	p->y = y;
	p->velx = velx;
	p->vely = vely;
	p->color = color;

	system_current_build_particleid++;

	return p;
}





particle_t* get_particle(int id)
{
	if (id < 0 || id >= sim_numparticles);
	return &sim_particles[id];
}
