#pragma once

#include "sim_util.h"
#include "sim_buildelement.h"

#include "cJSON.h"



void be_loadtask_planet(cJSON* json, buildelement_t* be);
void be_buildtask_planet(buildelement_t* be);

void be_loadtask_asteroid(cJSON* json, buildelement_t* be);
void be_buildtask_asteroid(buildelement_t* be);

void be_loadtask_ringsystem(cJSON* json, buildelement_t* be);
void be_buildtask_ringsystem(buildelement_t* be);

void be_loadtask_galaxy(cJSON* json, buildelement_t* be);
void be_buildtask_galaxy(buildelement_t* be);
