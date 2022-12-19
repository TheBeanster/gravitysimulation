#include "fileio.h"

#include "sim_valueflags.h"

#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS



cJSON* load_json(const char* filename)
{
	char* filebuffer = NULL;
	int filesize = 0;
	FILE* jsonfile = fopen(filename, "rb");

	if (!jsonfile)
	{
		printf("The file \"%s\" could not open!\n", filename);
		while (1)
		{

		}
		return 0;
	}

	fseek(jsonfile, 0, SEEK_END);
	filesize = ftell(jsonfile);
	fseek(jsonfile, 0, SEEK_SET);
	filebuffer = (char*)malloc(filesize + 1);
	if (filebuffer)
	{
		fread(filebuffer, 1, filesize, jsonfile);
	}
	fclose(jsonfile);
	filebuffer[filesize] = '\0';

	cJSON* json = cJSON_Parse(filebuffer);

	return json;
}


