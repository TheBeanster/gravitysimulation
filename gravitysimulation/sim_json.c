#include "sim_json.h"

#include "sim_valueflags.h"
#include <stdio.h>



int json_getdouble(cJSON* json, const char* name, double* val)
{
	cJSON* valjson = cJSON_GetObjectItem(json, name);
	if (!valjson) return 0;

	*val = valjson->valuedouble;

	//cJSON_Delete(valjson);
	return 1;
}



int json_getint(cJSON* json, const char* name, int* val)
{
	cJSON* valjson = cJSON_GetObjectItem(json, name);
	if (!valjson) return 0;

	*val = valjson->valueint;

	//cJSON_Delete(valjson);
	return 1;
}



int json_getbool(cJSON* json, const char* name, int* val)
{
	cJSON* valjson = cJSON_GetObjectItem(json, name);
	if (!valjson) return 0;

	*val = (valjson->valueint == 1);

	//cJSON_Delete(valjson);
	return 1;
}





int json_getdouble_flagchecked(cJSON* json, const char* name, double* val)
{
	cJSON* valjson = cJSON_GetObjectItem(json, name);
	if (!valjson) return 0;

	if (valjson->type == cJSON_String)
	{
		int valueflagid = get_valueflag_from_string(valjson->valuestring);
		if (!valueflagid) return 0;
		*val = valueflags[valueflagid].value;
	} else
	{
		*val = valjson->valuedouble;
	}

	//cJSON_Delete(valjson);
	return 1;
}








int json_getflags(cJSON* json, const char* name)
{
	NULLCHECK(json);

	cJSON* flagsjson = cJSON_GetObjectItem(json, name);
	NULLCHECK(flagsjson);

	// The combined flags
	int flags = 0;

	int numflags = cJSON_GetArraySize(flagsjson);
	for (int i = 0; i < numflags; i++)
	{
		cJSON* flagjson = cJSON_GetArrayItem(flagsjson, i);

		if (flagjson->type == cJSON_String)
		{
			int value = get_value_from_valueflag(flagjson->valuestring);
			flags |= value;
		}

	}

	return flags;
}
