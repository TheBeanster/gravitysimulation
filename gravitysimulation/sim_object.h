#pragma once

#include "sim_util.h"



typedef struct
{
	double x;
	double y;
	double velx;
	double vely;

	double mass;
	double radius;

} object_t;





/// <summary>
/// Sets the data for the object with the current build object id
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="velx"></param>
/// <param name="vely"></param>
/// <param name="mass"></param>
/// <param name="radius"></param>
/// <returns></returns>
object_t* create_object(
	double x,
	double y,
	double velx,
	double vely,
	double mass,
	double radius
);



/// <summary>
/// Get a pointer to an object in the world
/// </summary>
/// <param name="id">The id of the object</param>
/// <returns>Pointer to the object or NULL if id is out of bounds</returns>
object_t* get_object(int id);
