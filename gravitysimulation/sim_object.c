#include "sim_object.h"

#include "sim_system.h"
#include "sim_world.h"



object_t* create_object(
	double x,
	double y,
	double velx,
	double vely,
	double mass,
	double radius
)
{
	if (system_current_build_objectid >= system_objectcount) return 0;

	object_t* o = &sim_objects[system_current_build_objectid];

	o->x = x;
	o->y = y;
	o->velx = velx;
	o->vely = vely;
	o->mass = mass;
	o->radius = radius;
	
	system_current_build_objectid++;

	return o;
}





object_t* get_object(int id)
{
	if (id < 0 || id >= sim_numobjects);
	return &sim_objects[id];
}
