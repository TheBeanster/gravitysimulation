#pragma once

void*	mem_alloc(unsigned int size);
void	mem_free(void* block);

double	random_range(double min, double max);

double	distancesq(double x1, double y1, double x2, double y2);
double	distance(double x1, double y1, double x2, double y2);

int		stringindex(const char* const stringarray[], const int numstrings, const char* str);

double	lininterpolate(double a, double b, double bias);

double	fast_rsqrt(double number);

void	rotate(double angle, double* x, double* y);

double	get_angle(double x1, double y1, double x2, double y2);

#define ARRAYLENGTH(arr) sizeof(arr) / sizeof(arr[0])
#define NULLCHECK(ptr) if (!ptr) return 0
