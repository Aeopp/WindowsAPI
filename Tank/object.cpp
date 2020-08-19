#include "pch.h"
#include "object.h"


void object::initialize()
{
	set_b_update_location_from_owner(true);
	set_distance_from_owner({ 0,0 });

	_collision_component = std::make_unique<decltype(_collision_component)::element_type>();
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

void object::Hit(std::weak_ptr<object> _obj_weak)
{
	if (auto _object = _obj_weak.lock(); _object)
	{
		
	}
}

RECT object::get_collision_rect() const&
{
	return get_collision_component()->get_collision_rect(get_location(), get_size());
}


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


