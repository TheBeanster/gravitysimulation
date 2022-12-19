#include "sim_physics.h"

#include "sim_world.h"
#include "sim_chrono.h"
#include "sim_system.h"
#include <math.h>
#include <SDL_thread.h>





double gravitational_constant = 0.1;

double physics_iterations = 1.0;






#if USE_MULTITHREADING

SDL_Thread* threadpool[NUM_THREADS];
particle_thread_data_t thread_datapool[NUM_THREADS];

void update_physics()
{
	TIMER_START(thread_creation);
	for (int i = 0; i < NUM_THREADS; i++)
	{
		thread_datapool[i].idstart = (i * sim_numparticles) / NUM_THREADS;
		thread_datapool[i].idend = ((i + 1) * sim_numparticles) / NUM_THREADS - 1;
		threadpool[i] = SDL_CreateThread(update_particles, NULL, (void*)&thread_datapool[i]);
	}
	TIMER_END(thread_creation);
	//PRINT_TIMER(thread_creation);



	for (int i = 0; i < sim_numobjects; i++)
	{
		object_t* a = &sim_objects[i];

		for (int j = i; j < sim_numobjects; j++)
		{

			if (i != j)
			{

				object_t* b = &sim_objects[j];



				double dx = a->x - b->x;
				double dy = a->y - b->y;

				double dsquared = dx * dx + dy * dy;

				double fa = (gravitational_constant * b->mass) / dsquared;
				double fb = (gravitational_constant * a->mass) / dsquared;

				double d = sqrt(dsquared);

				if (d < b->radius + a->radius)
				{
					/*double massratio = b->mass / a->mass;
					a->velx = lininterpolate(a->velx, b->velx, massratio);
					a->vely = lininterpolate(a->vely, b->vely, massratio);
					b->velx = lininterpolate(b->velx, a->velx, massratio);
					b->vely = lininterpolate(b->vely, a->vely, massratio);*/

					continue;
				}

				dx /= d;
				dy /= d;



				a->velx -= fa * dx;
				a->vely -= fa * dy;

				b->velx += fb * dx;
				b->vely += fb * dy;

			}

		}

	}



	for (int i = 0; i < NUM_THREADS; i++)
	{
		SDL_WaitThread(threadpool[i], NULL);
	}



	for (int i = 0; i < sim_numobjects; i++)
	{
		object_t* o = &sim_objects[i];

		o->x += o->velx;
		o->y += o->vely;
	}

}



int update_particles(particle_thread_data_t* data)
{
	//printf("Thread: Start = %i, End = %i\n", data->idstart, data->idend);

	for (int i = data->idstart; i < data->idend; i++)
	{
		particle_t* p = &sim_particles[i];

		//if (p->x == INFINITY) continue;

		for (int j = 0; j < sim_numobjects; j++)
		{

			object_t* b = &sim_objects[j];

			double dx = p->x - b->x;
			double dy = p->y - b->y;

			double dsquared = dx * dx + dy * dy;

			double f = (gravitational_constant * b->mass) / dsquared;

		#if USE_FAST_INVERSE_SQUAREROOT
			double d = fast_rsqrt(dsquared);

			//if (d < b->radius) p->x == INFINITY;//continue;// d = b->radius;
			//if (d < b->radius) continue;

			dx *= d;
			dy *= d;
		#else
			double d = sqrt(dsquared);

			//if (d < b->radius) p->x == INFINITY;//continue;// d = b->radius;
			//if (d < b->radius) continue;

			dx /= d;
			dy /= d;
		#endif

			p->velx -= f * dx;
			p->vely -= f * dy;

		}

		p->x += p->velx;
		p->y += p->vely;


	}

	return 1;
}

#else

void update_physics()
{

	for (int i = 0; i < sim_numobjects; i++)
	{
		object_t* a = &sim_objects[i];

		if (a->x == INFINITY) continue;

		for (int j = i; j < sim_numobjects; j++)
		{

			if (i != j)
			{

				object_t* b = &sim_objects[j];

				if (b->x == INFINITY) continue;



				double dx = a->x - b->x;
				double dy = a->y - b->y;

				double dsquared = dx * dx + dy * dy;

				double fa = (gravitational_constant * b->mass) / dsquared;
				double fb = (gravitational_constant * a->mass) / dsquared;

				double d = sqrt(dsquared);

				if (d < b->radius + a->radius)
				{
					/*double massratio = b->mass / a->mass;
					a->velx = lininterpolate(a->velx, b->velx, massratio);
					a->vely = lininterpolate(a->vely, b->vely, massratio);
					b->velx = lininterpolate(b->velx, a->velx, massratio);
					b->vely = lininterpolate(b->vely, a->vely, massratio);*/
					//d *= a->radius + b->radius;
					continue;
				}

				dx /= d;
				dy /= d;



				a->velx -= fa * dx;
				a->vely -= fa * dy;

				b->velx += fb * dx;
				b->vely += fb * dy;

			}

		}

	}





	for (int i = 0; i < sim_numparticles; i++)
	{
		particle_t* p = &sim_particles[i];

		if (p->x == INFINITY) continue;

		for (int j = 0; j < sim_numobjects; j++)
		{

			object_t* b = &sim_objects[j];

			double dx = p->x - b->x;
			double dy = p->y - b->y;

			double dsquared = dx * dx + dy * dy;

			if (j == 0 && dsquared > escape_distance)
			{
				p->x = INFINITY;
				continue;
			}

			double f = (gravitational_constant * b->mass) / dsquared;

		#if USE_FAST_INVERSE_SQUAREROOT
			double d = fast_rsqrt(dsquared);

			//if (d < b->radius) p->x == INFINITY;//continue;// d = b->radius;
			//if (d < b->radius) continue;

			dx *= d;
			dy *= d;
		#else
			double d = sqrt(dsquared);

			if (d < b->radius) continue;//p->x = INFINITY;//continue;// d = b->radius;
			//if (d < b->radius) continue;

			dx /= d;
			dy /= d;
		#endif

			p->velx -= f * dx;
			p->vely -= f * dy;

		}

		p->velx *= particle_friction;
		p->vely *= particle_friction;

		p->x += p->velx;
		p->y += p->vely;

		
	}






	centerofmass_x = 0;
	centerofmass_y = 0;
	double totalmass = 0; // Combined mass of all objects

	for (int i = 0; i < sim_numobjects; i++)
	{
		object_t* o = &sim_objects[i];

		o->velx *= object_friction;
		o->vely *= object_friction;

		o->x += o->velx;
		o->y += o->vely;

		centerofmass_x += o->x * o->mass;
		centerofmass_y += o->y * o->mass;
		totalmass += o->mass;

		if (distancesq(sim_objects[0].x, sim_objects[0].y, o->x, o->y) > escape_distance)
		{
			o->x = INFINITY;
			continue;
		}

	}

	centerofmass_x /= totalmass;
	centerofmass_y /= totalmass;

}

#endif