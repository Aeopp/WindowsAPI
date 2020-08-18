#include "pch.h"
#include "object.h"

void object::initialize()
{
	set_b_update_location_from_owner(true);
	set_distance_from_owner({ 0,0 });
}

void object::render(HDC hdc)
{
	const auto _size_x = _size.first / 2;
	const auto _size_y = _size.second / 2;

	switch (_render_type_id)
	{
	case render_type::none:
		break;
	case render_type::rect:
		Rectangle(hdc, _location.first- _size_x, _location.second-_size_y, _location.first + _size_x, _location.second + _size_y);
		break;
	case render_type::circle:
		Ellipse(hdc, _location.first - _size_x, _location.second - _size_y, _location.first + _size_x, _location.second + _size_y);
		break;
	default:
		break;
	}
};

void object::release()
{

}

uint32_t object::get_layer_id() const&
{
	return layer_type::object;
}

void object::update()
{
	if (_owner && get_b_update_location_from_owner())
	{
		set_location(_owner->get_location() + this->get_distance_from_owner());
	}
}


