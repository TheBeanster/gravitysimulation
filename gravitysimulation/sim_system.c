#include "sim_system.h"

#include "sim_buildelement.h"
#include "sim_elementtypes.h"

#include "sim_object.h"
#include "sim_world.h"
#include "sim_camera.h"
#include "sim_physics.h"
#include "sim_json.h"

#include <stdio.h>
#include <string.h>
#include <math.h>



int system_objectcount = 0;
int system_particlecount = 0;

int system_current_build_objectid = 0;
int system_current_build_particleid = 0;



double escape_distance = INFINITY;
double particle_friction = 1;
double object_friction = 1;






void load_system_json(cJSON* json)
{
	int numglobals = cJSON_GetArraySize(json);
	
	JSON_GETDOUBLE(gravitational_constant);
	JSON_GETDOUBLE(physics_iterations);
	JSON_GETDOUBLE(particle_friction);
	JSON_GETDOUBLE(object_friction);
	if (json_getdouble(json, "friction", &object_friction)) // "friction" applies to both
	{
		particle_friction = object_friction;
	}

	JSON_GETDOUBLE(escape_distance);
	escape_distance *= escape_distance;

	JSON_GETDOUBLE(camera_x);
	JSON_GETDOUBLE(camera_y);
	JSON_GETDOUBLE(camera_zoom);

	JSON_GETINT(camera_focus_id);
	JSON_GETINT(camera_rotation_focus_id);
	JSON_GETINT(camera_mode);
	JSON_GETINT(camera_flags);







	cJSON* globalsjson = cJSON_GetObjectItem(json, "globals");
	NULLCHECK(globalsjson);

	for (int i = 0; i < numglobals; i++)
	{
		// For every object in global space

		cJSON* globaljson = cJSON_GetArrayItem(globalsjson, i);

		load_buildelement(globaljson, NULL);

	}
	
}









int init_simulation()
{
	printf("Initializing simulation\n");

	buildelement_t* belist_iterator = buildelementslist_begin;



	while (belist_iterator)
	{
		system_objectcount += belist_iterator->objectcount;
		system_particlecount += belist_iterator->particlecount;

		belist_iterator = belist_iterator->enext;
	}

	printf("Num objects   = %i\nNum particles = %i\n", system_objectcount, system_particlecount);

	sim_numobjects = system_objectcount;
	sim_objects = mem_alloc(sizeof(object_t) * sim_numobjects);

	sim_numparticles = system_particlecount;
	sim_particles = mem_alloc(sizeof(object_t) * sim_numparticles);



	printf("Activating all buildelements\n");

	system_current_build_objectid = 0;
	system_current_build_particleid = 0;

	belist_iterator = buildelementslist_begin;

	while (belist_iterator)
	{
		if (buildelement_typedata[belist_iterator->type].buildtask)
			buildelement_typedata[belist_iterator->type].buildtask(belist_iterator);

		belist_iterator = belist_iterator->enext;
	}

}
