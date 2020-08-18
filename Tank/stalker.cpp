#include "pch.h"
#include "stalker.h"

void stalker::update()
{
	super::update();

	if (!_target)return;

	{
		auto [x, y] = get_location() - _target->get_location();

		float flip_coordinate_plane_factor{};

		if (y < 0)
			flip_coordinate_plane_factor = 1.0f;
		else if (y > 0)
			flip_coordinate_plane_factor = -1.0f;

		const float l = std::sqrtf(x * x + y * y);
		const float radian = std::acosf(x / l);
		float _speed = get_speed();

		set_location(get_location() +
			std::pair<float, float>{-std::cosf(radian) * _speed,
			flip_coordinate_plane_factor* std::sinf(radian)* _speed});
	}
}

void stalker::initialize()
{
	super::initialize();

	set_speed(0.5f);
}
