#include "sim_util.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>





void* mem_alloc(unsigned int size)
{
	void* block = malloc(size);
	if (!block) exit(1);

	memset(block, 0, size);

	return block;
}

void mem_free(void* block)
{
	free(block);
}





double random_range(double min, double max)
{
	double n = (double)(rand()) / 32786.0;
	n *= (max - min);
	n += min;
	return n;
}





double distancesq(double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;

	return dx * dx + dy * dy;
}

double distance(double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;

	return sqrt(dx * dx + dy * dy);
}



int stringindex(const char* const stringarray[], const int numstrings, const char* str)
{
	if (!str) return -1;

	for (int i = 0; i < numstrings; i++)
	{
		if (strcmp(str, stringarray[i]))
		{
			return i;
		}
	}
	return -1;
}





double lininterpolate(double a, double b, double bias)
{
	return a + bias * (b - a);
}





double fast_rsqrt(double number)
{
	double y = number;
	double x2 = y * 0.5;
	long long i = *(long long*)&y;
	i = 0x5fe6eb50c7b537a9 - (i >> 1);
	y = *(double*)&i;
	y = y * (1.5 - (x2 * y * y));   // 1st iteration
	//      y  = y * ( 1.5 - ( x2 * y * y ) );   // 2nd iteration, this can be removed
	return y;
}



void rotate(double angle, double* x, double* y)
{
	double sinr = sin(angle);
	double cosr = cos(angle);
	double tempx = *x;
	*x = *x * cosr - *y * sinr;
	*y = tempx * sinr + *y * cosr;
}



double get_angle(double x1, double y1, double x2, double y2)
{
	double dx = x1 - x2;
	double dy = y1 - y2;
	double angle = acos(dx / sqrt(dx * dx + dy * dy));
	if (dy > 0) angle = -angle;
	return angle;
}
