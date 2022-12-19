#pragma once

#include "sim_util.h"

#define USE_FAST_INVERSE_SQUAREROOT 0

#define USE_MULTITHREADING 0



#ifdef USE_MULTITHREADING
#include <SDL_thread.h>
#endif



extern double gravitational_constant;

extern double physics_iterations;



#if USE_MULTITHREADING

#define NUM_THREADS 2

typedef struct
{
	int idstart;
	int idend;
} particle_thread_data_t;

extern SDL_Thread* threadpool[NUM_THREADS];
extern particle_thread_data_t thread_datapool[NUM_THREADS];



void update_physics();

int update_particles(particle_thread_data_t* data);

#else

void update_physics();

#endif