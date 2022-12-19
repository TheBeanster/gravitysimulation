#pragma once

#include <time.h>

double get_time(clock_t start, clock_t end);

#define TIMER_START(timername) clock_t timerstart_##timername = clock()
#define TIMER_END(timername) clock_t timerend_##timername = clock()
#define PRINT_TIMER(timername) printf(#timername " = %f\n", get_time(timerstart_##timername, timerend_##timername));
#define ENDPRINT_TIMER(timername) TIMER_END(timername); PRINT_TIMER(timername)
