#pragma once

#include <SDL.h>



typedef enum
{
	SYSTEMPINPUT_EXIT = 1U << 0,
} systeminput_t;

extern systeminput_t systeminputs;

extern char* keyboardinputs;



extern int mouse_position_x;
extern int mouse_position_y;

extern int mouse_delta_x;
extern int mouse_delta_y;

typedef enum
{
	MOUSEBUTTONSTATE_LEFT_DOWN = 1U << 0,
	MOUSEBUTTONSTATE_RIGHT_DOWN = 1U << 1,

} bean_mouse_button_state_t;

extern int mouse_button_states;



void update_inputs();

