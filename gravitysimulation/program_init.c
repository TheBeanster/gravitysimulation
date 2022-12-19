#include "program_main.h"

#include "sim_system.h"
#include "sim_trajectory.h"

#include "cJSON.h"
#include "fileio.h"
#include "system.h"



int program_init(int argc, char** argv)
{
	// Loading the system json

	cJSON* systemjson = 0;

	if (argc > 1)
	{
		// There is more than one argument, probably a system file
		printf("Loading system file \"%s\"\n", argv[1]);
		systemjson = load_json(argv[1]);

		if (!systemjson)
		{
			show_errorbox("Invalid system file!", "The system json file supplied through command line could not be loaded!");
			return 0;
		}

	} else
	{
		// If there are no arguments then try testsystem.json
		systemjson = load_json("testsystem.json");

		if (!systemjson)
		{
			show_errorbox("Invalid system file!", "The system json file supplied through command line could not be loaded!");
			return 0;
		}
	}

	

	load_system_json(systemjson);



	init_simulation();

	//init_trajectory(1000, 0);

	return 1;
}
