#include "sim_valueflags.h"
#include "sim_buildelement.h"

#include <stdio.h>
#include <math.h>





// An associative array of all string flags that can be used in json files
const valueflag_t valueflags[] =
{
	{"VF_NULL",						0},
	{"VF_STDDENSITY_TERRA",			5.5},
	{"VF_STDDENSITY_GASGIANT",		2.0},
	{"VF_STDDENSITY_STAR",			3.1},

	VALUEFLAG_ENUM(BEFLAG_COLOR_HUE_DISTANCE),
	VALUEFLAG_ENUM(BEFLAG_COLOR_SATURATION_DISTANCE),
	VALUEFLAG_ENUM(BEFLAG_COLOR_HUE_ANGLE),
	VALUEFLAG_ENUM(BEFLAG_COLOR_SATURATION_ANGLE),

	{"VF_INFINITY",					999999999999.9},
};





int get_valueflag_from_string(const char* str)
{
	if (!str) return 0;

	for (int i = 0; i < sizeof(valueflags) / sizeof(valueflags[0]); i++)
	{
		if (!strcmp(str, valueflags[i].name))
		{
			return i;
		}
	}

	printf("ERROR! : Invalid value flag \"%s\"\n", str);

	return 0;
}



double get_value_from_valueflag(const char* str)
{
	int valueflagid = get_valueflag_from_string(str);
	if (!valueflagid) return 0;
	return valueflags[valueflagid].value;
}
