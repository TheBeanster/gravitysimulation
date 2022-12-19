#include "sim_orbit.h"

#include "sim_buildelement.h"
#include "sim_physics.h"
#include "sim_json.h"

#include "fileio.h"

#include <math.h>





double orbital_velocity(buildelement_t* parent, double semimajoraxis, double dist)
{
	NULLCHECK(parent);

	return sqrt(parent->mass * gravitational_constant * (2.0 / dist - 1.0 / semimajoraxis));
}





void load_orbit(cJSON* json, orbit_t* orbit)
{
	JSON_GETDOUBLE(semimajoraxis, orbit->);
	JSON_GETDOUBLE(eccentricity, orbit->);
	JSON_GETDOUBLE(periapsis, orbit->);
	JSON_GETDOUBLE(apoapsis, orbit->);
	JSON_GETDOUBLE(argument, orbit->);
	
	JSON_GETBOOL(retrograde, orbit->);
	JSON_GETBOOL(oppositeside, orbit->);
}





void set_orbit(buildelement_t* be, orbit_t* orbit)
{
	NULLCHECK(be->parent);

	be->x = orbit->semimajoraxis;
	be->y = 0;

	be->velx = 0;
	be->vely = -orbital_velocity(be->parent, orbit->semimajoraxis, orbit->semimajoraxis);
	if (orbit->retrograde) be->vely = -be->vely;

	if (orbit->oppositeside)
	{
		be->x = -be->x;
		be->y = -be->y;
		be->velx = -be->velx;
		be->vely = -be->vely;
	}

	// Move forward by half it's velocity to even out it's circular orbit
	be->x += (be->velx / 2);
	be->y += (be->vely / 2);



	// Make the orbit relative to the parent
	be->x += be->parent->x;
	be->y += be->parent->y;

	be->velx += be->parent->velx;
	be->vely += be->parent->vely;


}
