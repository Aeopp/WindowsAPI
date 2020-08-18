#include "pch.h"
#include "barrel.h"
#include "game.h"
#include "bullet.h"

void barrel::update()
{
	super::update();

	if (GetAsyncKeyState(VK_RIGHT))
	{
		set_angle(get_angle() + get_angle_speed());
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		set_angle(get_angle() - get_angle_speed());
	}

	using namespace std;

	const auto radian_angle = math::degree_to_radian(get_angle());

	super::set_direction(
		{ cosf(radian_angle),
		sinf(radian_angle) });
}

void barrel::render(HDC hdc)
{

	super::render(hdc);

	const auto [x,y] = get_location();
	const auto [dx, dy] = get_direction();

	MoveToEx(hdc, (int)x, (int)y, nullptr);

	LineTo(hdc,(int)x+ dx*barrel_length,
			   (int)y+ dy* barrel_length);
}

void barrel::initialize()
{
	super::set_render_type(render_type::none);

	if (auto _owner = get_owner(); _owner!=nullptr)
	{
		super::set_location(_owner->get_location());
	}
}

uint32_t barrel::get_layer_id() const&
{
	return super::get_layer_id()+1;
}

void barrel::fire()&
{
	const auto [x,y] = get_direction();

	auto _bullet = game::instance().insert_object<bullet>();

	_bullet->set_direction(get_direction());
}
