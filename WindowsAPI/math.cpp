#include "pch.h"
#include "math.h"
#include "math.h"


float math::degree_to_radian(const float degree)
{
	static double factor = std::numbers::pi / 180;

	return factor * degree;
};

float math::radian_to_degree(const float radian)
{
	static double factor = 180 / std::numbers::pi;

	return factor * radian;
}
