#include "pch.h"
#include "shield.h"
#include "math.h"

void shield::initialize()
{
	super::initialize();

	super::set_size({ 50,50 });
	super::set_direction({ 1,0 });
	super::set_render_type(render_type::circle);
}

void shield::update()
{
	super::update();

	using namespace std;

	// cos = 内内 - 轿轿
	// sin = 轿内 + 内轿

	if (auto _owner = get_owner();_owner)
	{
		const auto _owner_location = _owner->get_location();

const		auto _owner_size = _owner->get_size();

const float _angle = get_angle();

const float _angle_radian = math::degree_to_radian(_angle);

object::set_angle(_angle + 0.5f);

		set_location({
			_owner_location.first + cosf(_angle_radian) * _owner_size.first,
			_owner_location.second + sinf(_angle_radian) * _owner_size.second
			});
	}
}

void shield::render(HDC hdc)
{
	super::render(hdc);
}
