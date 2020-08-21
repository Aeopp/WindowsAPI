#include "stdafx.h"
#include "timer.h"

timer* timer::m_pInstance = nullptr;

timer::timer()
{
}

timer::~timer()
{
	
}

void timer::Update(float _dt)
{
	dt = _dt;
}

 timer* timer::Get_Instance()
{
	if (!timer::m_pInstance)
		timer::m_pInstance = new timer;
	return timer::m_pInstance;
}

 void timer::Destroy_Instance()
{
	SAFE_DELETE(timer::m_pInstance);
}
