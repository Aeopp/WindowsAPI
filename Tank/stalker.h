#pragma once
#include "monster.h"

class stalker : public monster
{
private:
	using super = monster; 
	std::shared_ptr<class object> _target{ nullptr };
public:
	virtual void update()override;
	virtual void initialize()override;
public:
	inline void set_target(decltype(_target) _target)&;
};


inline void stalker::set_target(decltype(_target) _target)&
{
	this->_target = std::move(_target);
}


