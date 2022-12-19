#include "sim_elementtypes.h"

#include "sim_object.h"
#include "sim_particle.h"
#include "sim_system.h"
#include "sim_physics.h"

#include "fileio.h"
#include <stdio.h>
#include <math.h>
#include <string.h>







void be_loadtask_planet(cJSON* json, buildelement_t* be)
{
	be->objectcount = 1;
}

void be_buildtask_planet(buildelement_t* be)
{
	create_object
	(
		be->x,
		be->y,
		be->velx,
		be->vely,
		be->mass,
		be->radius
	);
}





void be_loadtask_asteroid(cJSON* json, buildelement_t* be)
{
	be->particlecount = 1;
}

void be_buildtask_asteroid(buildelement_t* be)
{
	color_t color; color.color = 0xffffffff;
	create_particle
	(
		be->x,
		be->y,
		be->velx,
		be->vely,
		color
	);

}





void be_loadtask_ringsystem(cJSON* json, buildelement_t* be)
{
	// A parent is required
	NULLCHECK(be->parent);

	json_getint(json, "particlecount", &be->particlecount);
}

void be_buildtask_ringsystem(buildelement_t* be)
{
	// A parent is required
	NULLCHECK(be->parent);

	for (int i = 0; i < be->particlecount; i++)
	{
		double distscalar = random_range(0.0, 1.0);
		double dist = lininterpolate(be->rmin, be->rmax, distscalar);
		//double dist = sqrt(random_range(be->rmin * be->rmin, be->rmax * be->rmax));
		//double distscalar = lininterpolate(be->rmin, be->rmax, dist);
		double posangle = random_range(0, 3.141592659 * 2.0);
		double velangle = posangle + random_range(-3.141592659, 3.141592659) * be->random;

		double vel = sqrt(be->parent->mass * gravitational_constant * (1 / dist));



		double hue = 0.0;
		double saturation = 1.0;

		if (be->flags & BEFLAG_COLOR_HUE_ANGLE)
		{
			hue = RADIANSTOANGLE(posangle);
			saturation = 1.0;
		}
		else if (be->flags & BEFLAG_COLOR_HUE_DISTANCE)
		{
			hue = distscalar * 360.0;
			saturation = 1.0;
		}

		if (be->flags & BEFLAG_COLOR_SATURATION_ANGLE)
		{
			saturation = RADIANSTOANGLE(posangle);
		}
		else if (be->flags & BEFLAG_COLOR_SATURATION_DISTANCE)
		{
			saturation = distscalar * 360.0;
		}

		color_t color = color_from_hsv(
			hue,
			saturation,
			1.0);



		particle_t* p = create_particle(
			cos(posangle) * dist + be->parent->x,
			sin(posangle) * dist + be->parent->y,
			sin(velangle) * vel,
			-cos(velangle) * vel,
			color
		);

		if (be->retrograde)
		{
			p->velx = -p->velx;
			p->vely = -p->vely;
		}

		p->x += (p->velx / 2);
		p->y += (p->vely / 2);

		p->velx += be->parent->velx;
		p->vely += be->parent->vely;
	}
}





void be_loadtask_galaxy(cJSON* json, buildelement_t* be)
{
	// A parent is required
	NULLCHECK(be->parent);

	json_getint(json, "objectcount", &be->objectcount);
}

void be_buildtask_galaxy(buildelement_t* be)
{
	// A parent is required
	NULLCHECK(be->parent);

	for (int i = 0; i < be->objectcount; i++)
	{
		double dist = sqrt(random_range(be->rmin * be->rmin, be->rmax * be->rmax));
		double angle = random_range(0, 3.141592659 * 2.0);

		double vel = sqrt(be->parent->mass * gravitational_constant * (1 / dist));

		object_t* o = create_object(
			cos(angle) * dist + be->parent->x,
			sin(angle) * dist + be->parent->y,
			sin(angle) * vel,
			-cos(angle) * vel,
			be->mass,
			be->radius
		);

		if (be->retrograde)
		{
			o->velx = -o->velx;
			o->vely = -o->vely;
		}

		o->x += (o->velx / 2);
		o->y += (o->vely / 2);
		
		o->velx += be->parent->velx;
		o->vely += be->parent->vely;
	}
}
