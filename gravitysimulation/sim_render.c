#include "sim_render.h"

#include "sim_world.h"

#include "system.h"
#include "sim_camera.h"

#include <stdio.h>
#include <math.h>



double cam_sinr = 0;
double cam_cosr = 0;



void render_simulation()
{

	cam_sinr = sin(camera_render_rotate);
	cam_cosr = cos(camera_render_rotate);



	SDL_SetRenderDrawColor(main_renderer, 255, 255, 255, 255);
	
	for (int i = 0; i < sim_numobjects; i++)
	{
		object_t* o = &sim_objects[i];

		if (o->x == INFINITY) continue;

		double movx = o->x - camera_render_x;
		double movy = o->y - camera_render_y;
		double posx = movx * cam_cosr - movy * cam_sinr;
		double posy = movx * cam_sinr + movy * cam_cosr;
		
		SDL_RenderDrawPoint(
			main_renderer,
			(posx * camera_zoom) + (screenwidth >> 1),
			(posy * camera_zoom) + (screenheight >> 1));
	}



	SDL_SetRenderDrawColor(main_renderer, 255, 255, 0, 255);

	for (int i = 0; i < sim_numparticles; i++)
	{
		particle_t* p = &sim_particles[i];

		if (p->x == INFINITY) continue;

		double movx = p->x - camera_render_x;
		double movy = p->y - camera_render_y;
		double posx = movx * cam_cosr - movy * cam_sinr;
		double posy = movx * cam_sinr + movy * cam_cosr;

		SDL_SetRenderDrawColor(
			main_renderer,
			p->color.rgba.r,
			p->color.rgba.g,
			p->color.rgba.b,
			p->color.rgba.a);

		SDL_RenderDrawPoint(
			main_renderer,
			(posx * camera_zoom) + (screenwidth >> 1),
			(posy * camera_zoom) + (screenheight >> 1));
	}
}





void render_point_in_world(double x, double y)
{
	if (x == INFINITY) return;

	double movx = x - camera_render_x;
	double movy = y - camera_render_y;
	double posx = movx * cam_cosr - movy * cam_sinr;
	double posy = movx * cam_sinr + movy * cam_cosr;

	SDL_RenderDrawPoint(
		main_renderer,
		(posx * camera_zoom) + (screenwidth >> 1),
		(posy * camera_zoom) + (screenheight >> 1));
}
