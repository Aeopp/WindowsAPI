#include "pch.h"
#include "game.h"
#include "object.h"
#include "player.h"
#include "monster.h"
#include "shield.h"

void game::render(HDC hdc)
{
	for (auto& objects : object_list)
	{
		for (auto& _object : objects.second)
		{
			_object->render(hdc);
		}
	}
};

void game::update()
{
	for (auto& objects : object_list)
	{
		for (auto& _object : objects.second)
		{
			_object->update();
		}
	}
}

void game::initialize()
{
	auto _player = insert_object<player>();

	auto _monster = insert_object<monster>();
	_monster->set_size({ 50.0f ,  50.0f });
	_monster->set_location({ 200,200 });

	_monster = insert_object<monster>();
	_monster->set_size({50.0f,50.0f});
	_monster->set_location({600,200});
}

void game::release()
{
	for (auto& objects : object_list)
	{
		for (auto& _object : objects.second)
		{
			_object->release();
		}
	}
}
