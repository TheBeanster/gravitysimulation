#pragma once

#include "sim_util.h"
#include "sim_orbit.h"
#include "sim_color.h"

#include "cJSON.h"





// General purpose flags
typedef enum
{
	BEFLAG_COLOR_HUE_DISTANCE			= (1U << 0), // Set things' hue based on distance
	BEFLAG_COLOR_SATURATION_DISTANCE	= (1U << 1), // Set things' saturation based on distance
	BEFLAG_COLOR_HUE_ANGLE				= (1U << 2), // Set things' hue based on angle
	BEFLAG_COLOR_SATURATION_ANGLE		= (1U << 3), // Set things' saturation based on angle

} buildelement_flags_t;






typedef struct buildelement_t_
{
	struct buildelement_t_* eprev;
	struct buildelement_t_* enext;

	int type;

	buildelement_flags_t flags;

	struct buildelement_t_* parent;

	int objectcount; // Number of objects created by this element
	int particlecount; // Number of particles created by this element

	double x;
	double y;
	double velx;
	double vely;
	color_t color;

	double mass;
	double radius;

	double density;

	orbit_t orbit;
	int retrograde; // Bool, probably remove eventually and just use the retrograde flag in orbit var

	double rmin;
	double rmax;

	double random;

} buildelement_t;



typedef void (buildelement_loadtask)(cJSON*, buildelement_t*);

typedef void (buildelement_buildtask)(buildelement_t*);



typedef struct
{
	const char* name;
	buildelement_loadtask* loadtask;
	buildelement_buildtask* buildtask;
} buildelement_typedata_t;

extern const buildelement_typedata_t buildelement_typedata[];





/// <summary>
/// Gets the build element type index from a string
/// </summary>
/// <param name="str">The string to index from</param>
/// <returns>The build element type index. Or BETYPE_NULL if no match was found</returns>
int get_element_type_from_string(const char* str);








extern buildelement_t* buildelementslist_begin;
extern buildelement_t* buildelementslist_end;





/// <summary>
/// Allocates and links a new build element
/// </summary>
/// <returns>The new empty build element</returns>
buildelement_t* create_buildelement();





/// <summary>
/// Loads build element data from a json object
/// </summary>
/// <param name="json">The build element json object to load from</param>
/// <param name="parent">The buildelement which this is a child of</param>
/// <returns>A pointer to the new build element</returns>
buildelement_t* load_buildelement(cJSON* json, buildelement_t* parent);





/// <summary>
/// Deletes all build elements in the list
/// </summary>
void delete_buildelements();


