#include "sim_buildelement.h"

#include "sim_object.h"
#include "sim_particle.h"
#include "sim_elementtypes.h"

#include "fileio.h"
#include "sim_json.h"
#include <stdio.h>
#include <math.h>
#include <string.h>





const buildelement_typedata_t buildelement_typedata[] =
{
	{"BETYPE_NULL",			0,								0},
	{"BETYPE_PLANET",		&be_loadtask_planet,			&be_buildtask_planet},
	{"BETYPE_ASTEROID",		&be_loadtask_asteroid,			&be_buildtask_asteroid},
	{"BETYPE_RINGSYSTEM",	&be_loadtask_ringsystem,		&be_buildtask_ringsystem},
	{"BETYPE_GALAXY",		&be_loadtask_galaxy,			&be_buildtask_galaxy},
	
};



buildelement_t* buildelementslist_begin = 0;
buildelement_t* buildelementslist_end = 0;





int get_element_type_from_string(const char* str)
{
	if (!str) return -1;

	for (int i = 0; i < ARRAYLENGTH(buildelement_typedata); i++)
	{
		if (!strcmp(str, buildelement_typedata[i].name))
		{
			return i;
		}
	}
	return -1;
}






buildelement_t* create_buildelement()
{
	buildelement_t* be = mem_alloc(sizeof(buildelement_t));

	// Link it to the list

	if (buildelementslist_begin == 0)
	{
		// List is empty
		buildelementslist_begin = be;
	}

	if (buildelementslist_end)
		buildelementslist_end->enext = be;

	be->eprev = buildelementslist_end;
	buildelementslist_end = be;

	return be;
}





buildelement_t* load_buildelement(cJSON* json, buildelement_t* parent)
{
	NULLCHECK(json);



	buildelement_t* be = create_buildelement();
	


	// Set the parent
	be->parent = parent;



	// Get the type of the element
	cJSON* typejson = cJSON_GetObjectItem(json, "type");
	NULLCHECK(typejson);
	
	printf("Loading build element of type: \"%s\"\n", typejson->valuestring);

	be->type = get_element_type_from_string(typejson->valuestring);
	if (be->type == -1) return 0;



	be->flags = json_getflags(json, "flags");
	


	// TODO Clean this up real nice

	JSON_GETDOUBLE(x, be->);
	JSON_GETDOUBLE(y, be->);
	JSON_GETDOUBLE(velx, be->);
	JSON_GETDOUBLE(vely, be->);
	JSON_GETDOUBLE(mass, be->);
	JSON_GETDOUBLE(rmin, be->);
	JSON_GETDOUBLE(rmax, be->);
	JSON_GETDOUBLE(random, be->);
	JSON_GETBOOL(retrograde, be->);

	// Density specification is prioritized over radius
	if (!json_getdouble_flagchecked(json, "density", &be->density))
	{
		JSON_GETDOUBLE(radius, be->);
	}

	cJSON* orbitjson = cJSON_GetObjectItem(json, "orbit");
	if (orbitjson)
	{
		load_orbit(orbitjson, &be->orbit);

		set_orbit(be, &be->orbit);
	}



	// Run it's load task
	// This is done AFTER the loading the standard variables so that this can override those values
	if (buildelement_typedata[be->type].loadtask)
		buildelement_typedata[be->type].loadtask(json, be);





	// Array of this build elements children jsons
	cJSON* childrenjson = cJSON_GetObjectItem(json, "children");
	if (childrenjson)
	{
		// This element has children 

		int numchildren = cJSON_GetArraySize(childrenjson);
		for (int i = 0; i < numchildren; i++)
		{
			// Recursively load it's children, (EXTREMELY EPIC)
			cJSON* childjson = cJSON_GetArrayItem(childrenjson, i);
			load_buildelement(childjson, be);
		}
	}


	return be;
}







void delete_buildelements()
{
	buildelement_t* be_iterator = buildelementslist_begin;

	while (be_iterator)
	{
		buildelement_t* del = be_iterator;
		be_iterator = be_iterator->enext;
		mem_free(del);
	}
}

