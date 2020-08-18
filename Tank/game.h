#pragma once
#include "pch.h"
#include "singleton_interface.h"

class game : public singleton_interface<game>
{
public :
	void render(HDC hdc)override;
	void update()override;
	void initialize()override;
	void release()override;
public:
	std::map<uint32_t,std::list<std::shared_ptr<class object>>> object_list;
	template<typename object_type> 
	[[nodiscard]] auto insert_object();
};

template<typename object_type>
[[nodiscard]] auto game::insert_object()
{
	std::shared_ptr<object_type> _ptr = std::make_shared<object_type>();

	_ptr->set_ptr(_ptr);

	_ptr->initialize();

	object_list[_ptr->get_layer_id()].push_back(_ptr);

	return _ptr;
};

