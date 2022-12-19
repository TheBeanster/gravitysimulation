#pragma once

#include "sim_util.h"
#include "cJSON.h"



int json_getdouble(cJSON* json, const char* name, double* val);

int json_getint(cJSON* json, const char* name, int* val);

int json_getbool(cJSON* json, const char* name, int* val);

int json_getdouble_flagchecked(cJSON* json, const char* name, double* val);



#define JSON_GETINT(name, loc) json_getint(json, #name, &loc name)
#define JSON_GETDOUBLE(name, loc) json_getdouble(json, #name, &loc name)
#define JSON_GETBOOL(name, loc) json_getbool(json, #name, &loc name)



int json_getflags(cJSON* json, const char* name);
