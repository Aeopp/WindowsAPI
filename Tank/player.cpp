#include "pch.h"
#include "player.h"
#include "shield.h"
#include "game.h"
#include "barrel.h"

void player::update()
{
	super::update();

	if (GetAsyncKeyState(VK_LEFT))
	{
		set_direction({-1,0}); moveable_object::move();
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		set_direction({+1,0}); moveable_object::move();
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		set_direction({ 0,-1 });
		moveable_object::move();
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		set_direction({ 0,+1 });
		moveable_object::move();
	}
};
 void player::render(HDC hdc)
{
	 super::render(hdc);
};
 void player::initialize()
 {
	 super::initialize();

	 object::set_location({ 500,500 });
	 object::set_size({ 100,100 });

	 _barrel = game::instance().insert_object<barrel>();
	 _barrel->set_owner(get_my_ptr().lock());

	 for (size_t i = 0; i < 4; ++i)
	 {
		 auto _shield = game::instance().insert_object<shield>();
		 _shield->set_owner(object::get_my_ptr().lock());
		 _shield->set_angle({ 360.0f * (i+1) / 4 });
	 }
 };

void player::release()
{
	super::release();
}

void player::fire()
{
	
}

