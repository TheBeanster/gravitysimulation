#include "sim_camera.h"

#include "sim_world.h"
#include "input.h"
#include <stdio.h>
#include <math.h>



double camera_x = 0; // Position relative to target
double camera_y = 0; // Position relative to target
double camera_rotate = 0;
double camera_zoom = 1;

double camera_target_x = 0;
double camera_target_y = 0;
double camera_target_rotate = 0;

double camera_render_x = 0; // Position used when rendering
double camera_render_y = 0; // Position used when rendering
double camera_render_rotate = 0; // Rotation used when rendering



camera_targetmode_t camera_mode = CAMERAMODE_CENTEROFMASS;
camera_flags_t camera_flags = 0;



int camera_focus_id = 0;
int camera_rotation_focus_id = 0;






void update_camera()
{

	double mouse_delta_rot_x = (double)mouse_delta_x / camera_zoom;
	double mouse_delta_rot_y = (double)mouse_delta_y / camera_zoom;
	rotate(
		-camera_render_rotate + camera_target_rotate,
		&mouse_delta_rot_x,
		&mouse_delta_rot_y);

	if (mouse_button_states & MOUSEBUTTONSTATE_LEFT_DOWN)
	{
		camera_x -= mouse_delta_rot_x;
		camera_y -= mouse_delta_rot_y;
	}



	if (keyboardinputs[SDL_SCANCODE_Z])
	{
		camera_zoom *= 1.05f;
	}

	if (keyboardinputs[SDL_SCANCODE_X])
	{
		camera_zoom /= 1.05f;
	}

	if (keyboardinputs[SDL_SCANCODE_LEFT])
	{
		camera_rotate -= 0.02;
	}

	if (keyboardinputs[SDL_SCANCODE_RIGHT])
	{
		camera_rotate += 0.02;
	}



	

	switch (camera_mode)
	{
	case CAMERAMODE_STATIONARY:
		camera_target_x = 0;
		camera_target_y = 0;
		camera_target_rotate = 0;
		break;
		
	case CAMERAMODE_CENTEROFMASS:
		camera_target_x = centerofmass_x;
		camera_target_y = centerofmass_y;
		break;

	case CAMERAMODE_FOCUSOBJECT:{}
		particle_t* f; // Focus
		if (camera_flags & CAMERAFLAG_FOCUSPARTICLE)
			f = get_particle(camera_focus_id);
		else
			f = (particle_t*)get_object(camera_focus_id);
		if (!f) break;

		camera_target_x = f->x;
		camera_target_y = f->y;

		if (camera_flags & CAMERAFLAG_ROTATEWITHFOCUS)
		{
			particle_t* r; // Rotation focus
			if (camera_flags & CAMERAFLAG_FOCUSPARTICLE)
				r = get_particle(camera_rotation_focus_id);
			else
				r = (particle_t*)get_object(camera_rotation_focus_id);
			if (!r) break;

			// Get the angle between the focus and the rotation focus

			camera_target_rotate = get_angle(f->x, f->y, r->x, r->y);
		}
		
		break;

	default:
		break;
	}



	double camx = camera_x;
	double camy = camera_y;
	rotate(-camera_target_rotate, &camx, &camy);

	camera_render_x = camx + camera_target_x;
	camera_render_y = camy + camera_target_y;
	camera_render_rotate = camera_rotate + camera_target_rotate;
}
