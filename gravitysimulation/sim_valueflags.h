#pragma once

#include "sim_util.h"

// Array elements in an associative array
typedef struct
{
	const char* name;
	double value;
} valueflag_t;



// Creates a name, enum pair
#define VALUEFLAG_ENUM(name) {#name, name}

extern const valueflag_t valueflags[];



/// <summary>
/// Gets the index of a value flag from a string
/// </summary>
/// <param name="str">The string to match against</param>
/// <returns>The index of the flag with a matching name as str. Or 0 if no match was found</returns>
int get_valueflag_from_string(const char* str);

/// <summary>
/// Gets the value of a valueflag from a string
/// </summary>
/// <param name="str">The string to match against</param>
/// <returns>The value of the flag</returns>
double get_value_from_valueflag(const char* str);
