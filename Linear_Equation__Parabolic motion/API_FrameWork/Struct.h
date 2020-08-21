#pragma once

#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct tagInfo
{
	float	fX;
	float	fY;
	int		iCX;
	int		iCY;
}INFO;

struct vec
{
	float x;
	float y;
};

template<typename T>
T operator-(const T& lhs, const T& rhs)
{
	const auto& [x, y] = lhs;
	const auto& [x1, y1] = rhs;

	return { x - x1,y1 - y };
}

struct segment
{
	vec v0;
	vec v1;
};

#endif // !__STRUCT_H__
