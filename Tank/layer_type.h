#pragma once
#include <numeric>

using uint32_t = unsigned int;
#define number(idx)  idx /  (2ll<<32)

enum layer_type : uint32_t
{
	object = number(1),
	effect = number(2),
	UI = number(3),
	none  = number(2ll<<32),
};
