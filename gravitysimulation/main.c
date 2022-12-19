#include <SDL.h>
#include <stdio.h>
#include "system.h"
#include "input.h"
#include "program_main.h"





int main(int argc, char** argv)
{

	if (!system_init()) return 1;
	
	if (!program_init(argc, argv)) return 1;
	


	while (!(systeminputs & SYSTEMPINPUT_EXIT))
	{
		
		update_inputs();

		program_loop();

		update_window();

		framecount++;
	}



	program_quit();

	system_quit();

	return 0;
}
