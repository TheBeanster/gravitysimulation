#pragma once

#include "sim_util.h"



extern double camera_x;
extern double camera_y;
extern double camera_rotate;
extern double camera_zoom;

extern double camera_target_x;
extern double camera_target_y;
extern double camera_target_rotate;

extern double camera_render_x;
extern double camera_render_y;
extern double camera_render_rotate;



typedef enum
{
	CAMERAMODE_STATIONARY, // Don't move the target
	CAMERAMODE_CENTEROFMASS, // Center the camera on the center of mass
	CAMERAMODE_FOCUSOBJECT, // Center the camera on the position of an object
} camera_targetmode_t;
extern camera_targetmode_t camera_mode;

typedef enum
{
	CAMERAFLAG_FOCUSPARTICLE = 1U << 0, // The camera_focus_id is a particle id
	CAMERAFLAG_ROTATEWITHFOCUS = 1U << 1, // The camera should rotate with the camera_rotation_focus_id
	CAMERAFLAG_ROTATIONFOCUSPARTICLE = 1U << 2, // The rotation focus id is a particle id
} camera_flags_t;
extern camera_flags_t camera_flags;



extern int camera_focus_id;
extern int camera_rotation_focus_id;





void update_camera();
