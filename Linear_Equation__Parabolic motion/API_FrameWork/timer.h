#pragma once

#ifndef __TIMER__H__
#define __TIMER__H__
#include <list>
#include "Define.h"
#include "Enum.h"

class timer
{
private:
	timer();
	~timer();
public:
	void Update(float _dt);
	float dt{ 0.f };
public:
	static timer* Get_Instance();
	static void Destroy_Instance();
private:
	std::list<class CObj*>			m_listObj[OBJID::END];
	static timer* m_pInstance;
};


#endif // !__TIMER__H__
