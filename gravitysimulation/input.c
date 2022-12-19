#include "input.h"

#include <SDL.h>



systeminput_t systeminputs = 0;

char* keyboardinputs = NULL;

int mouse_position_x = 0;
int mouse_position_y = 0;

int mouse_delta_x = 0;
int mouse_delta_y = 0;

int mouse_button_states = 0;





void update_inputs()
{
	SDL_Event e;

	systeminputs = 0;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			systeminputs |= SYSTEMPINPUT_EXIT;
		}
	}



	mouse_delta_x = -mouse_position_x;
	mouse_delta_y = -mouse_position_y;

	int mouse_button_state = SDL_GetMouseState(&mouse_position_x, &mouse_position_y);

	mouse_delta_x += mouse_position_x;
	mouse_delta_y += mouse_position_y;

	mouse_button_states = 0;
	if (mouse_button_state & SDL_BUTTON(1)) mouse_button_states |= MOUSEBUTTONSTATE_LEFT_DOWN;
	if (mouse_button_state & SDL_BUTTON(3)) mouse_button_states |= MOUSEBUTTONSTATE_RIGHT_DOWN;


}
