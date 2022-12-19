#pragma once

#include "sim_util.h"

#include "cJSON.h"



// Utility struct for storing orbit info
typedef struct
{
	double semimajoraxis; // Average high in the orbit
	double eccentricity;
	double periapsis; // Lowest point in the orbit
	double apoapsis; // Highest point in the orbit
	double argument; // Angle of periapse
	double epoch; // Time of orbit to spawn at
	int retrograde; // Bool
	int oppositeside; // Bool, just a debug until orbital argument is properly implemented
} orbit_t;



/// <summary>
/// Calculates the velocity of an orbit with the given semimajor axis using the vis-viva equation
/// </summary>
/// <param name="be">Pointer to the parent of the orbit</param>
/// <param name="semimajoraxis">Semimajor axis of the orbit</param>
/// <param name="dist">The distance from the parent build element</param>
/// <returns>The orbital velocity of the given parameters</returns>
double orbital_velocity(struct buildelement_t* parent, double semimajoraxis, double dist);

// TODO Make a function that uses an orbit struct





/// <summary>
/// Loads orbit data from a json object. If multiple attributes describing orbit size are contradicting,
/// then persiapse and apoapse will take priority
/// </summary>
/// <param name="json">Json object to load from</param>
/// <param name="orbit">Pointer to the orbit struct to load to</param>
void load_orbit(cJSON* json, orbit_t* orbit);



/// <summary>
/// Applies the orbit attributes to the x, y, velx, and vely member of a build element
/// </summary>
/// <param name="be">The build element to set</param>
/// <param name="orbit">The orbit to use</param>
void set_orbit(struct buildelement_t* be, orbit_t* orbit);

// TODO Add a function to set orbit to objects and particles
