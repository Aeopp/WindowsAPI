#include "pch.h"
#include "moveable_object.h"

void moveable_object::move()&
{
	auto current_location = get_location();

	object::set_location(
		{ current_location.first + direction.first, current_location.second + direction.second});
}
