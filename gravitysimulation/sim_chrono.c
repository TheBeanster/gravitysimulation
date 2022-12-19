#include "sim_chrono.h"

#include <time.h>

double get_time(clock_t start, clock_t end)
{
	long delta = end - start;
	return (delta) / (double)CLOCKS_PER_SEC;
}
