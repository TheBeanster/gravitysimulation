#include "program_main.h"

#include "system.h"
#include "input.h"

#include <stdio.h>
#include "sim_util.h"
#include "sim_object.h"
#include "sim_camera.h"
#include "sim_physics.h"
#include "sim_world.h"
#include "sim_render.h"
#include "sim_chrono.h"
#include "sim_color.h"
#include "sim_trajectory.h"



void program_loop()
{
	SDL_SetRenderTarget(main_renderer, main_texture);
	SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 255);
	SDL_RenderClear(main_renderer);



	if (keyboardinputs[SDL_SCANCODE_Q]) physics_iterations *= 1.1;
	if (keyboardinputs[SDL_SCANCODE_A]) physics_iterations /= 1.1;
	if (physics_iterations < 1) physics_iterations = 1;



	//update_particle_trajectory();



	TIMER_START(physics);
	for (int i = 0; i < physics_iterations; i++)
	{
		update_physics();
	}
	TIMER_END(physics);
	//PRINT_TIMER(physics);

	

	update_camera();



	render_simulation();
	
	//render_particle_trajectory();

	/*printf(
		"Physics time = %f, Render time = %f\n",
		get_time(timerstart_physics, timerend_physics),
		get_time(timerstart_render, timerend_render));*/

}
