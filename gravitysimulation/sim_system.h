#pragma once

#include "sim_util.h"

#include "cJSON.h"



extern int system_objectcount;
extern int system_particlecount;

extern int system_current_build_objectid;
extern int system_current_build_particleid;

extern double escape_distance;
extern double particle_friction;
extern double object_friction;



void load_system_json(cJSON* json);



/// <summary>
/// Fills the simulation objects and particles with the data created from the spawn list
/// </summary>
/// <returns>Error data</returns>
int init_simulation();
