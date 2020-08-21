#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "ObjMgr.h"
#include "GuideBullet.h"
#include "timer.h"
#include <string>
#include <sstream>


CPlayer::CPlayer()
	: m_fCannon(0.f)
{
	ZeroMemory(&m_tPosin, sizeof(m_tPosin));
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;

	m_fSpeed = 5.f;
	m_fCannon = 100.f;

	m_fForce = 10.f;
}

int CPlayer::Update()
{
	//200,500 ~ 400,350

	bool b_line = false;

	if (m_tInfo.fX >= 200 && m_tInfo.fX <= 400 && m_tInfo.fY <= 500 &&
		m_tInfo.fY >= 350)
	{
		float rad = atan2f((500 - 350) ,(400 - 200));
		
		dir_x= cos(rad);
		dir_y = sin(rad);

		b_line = true;
	}
	else
	{
		dir_x = 0;
		dir_y = 0;
		b_line = false;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_fAngle += 5.0f;

		if(!b_line)
		m_tInfo.fX += -1 * m_fSpeed;

		if (b_line)
		{
			m_tInfo.fX += -dir_x * m_fSpeed;
			m_tInfo.fY += dir_y * m_fSpeed;

		}
	
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_fAngle -= 5.0f;

		if (!b_line)
		m_tInfo.fX += 1* m_fSpeed;

		if (b_line)
		{
			m_tInfo.fX += +dir_x * m_fSpeed;
			m_tInfo.fY += -dir_y * m_fSpeed;

		}
	}
	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY += -1 * m_fSpeed;
		

		/*m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;*/
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += 1 * m_fSpeed;

		/*m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * -m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * -m_fSpeed;*/
	}
	if (GetAsyncKeyState(VK_SPACE))
		jump();
	if (GetAsyncKeyState(VK_SHIFT))
	{
		int i = 1;

		CObjMgr::Get_Instance()->Add_Object(Create_Bullet<CBullet>(), OBJID::BULLET);
	}
		
	if (GetAsyncKeyState('A'))
		CObjMgr::Get_Instance()->Add_Object(Create_Shield(), OBJID::SHIELD);
	if (GetAsyncKeyState('S'))
		CObjMgr::Get_Instance()->Add_Object(Create_Bullet<CScrewBullet>(), OBJID::BULLET);
	if (GetAsyncKeyState('D'))
		CObjMgr::Get_Instance()->Add_Object(Create_Bullet<CGuideBullet>(), OBJID::BULLET);

	if (t >= 2)
	{
		bJump = false;
	}

	if (bJump)
	{
		t += 0.01538461538461538f;

		m_tInfo.fX += jump_dir_x * m_fForce;
		m_tInfo.fY -= jump_dir_y * m_fForce;

		m_tInfo.fY += (9.8f * t);
	}
	else
	{
		 t = jump_dir_x = jump_dir_y = 0;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	m_tPosin.x = (LONG)(m_tInfo.fX + cosf(m_fAngle * PI / 180.f) * m_fCannon);
	m_tPosin.y = (LONG)(m_tInfo.fY - sinf(m_fAngle * PI / 180.f) * m_fCannon);
}

void CPlayer::Render(HDC _DC)
{
	Update_Rect();
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	MoveToEx(_DC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(_DC, m_tPosin.x, m_tPosin.y);

	std::wstringstream wss;
	wss << L"최고점 도달 시간 : " << std::to_wstring(high_t) << std::endl;
	auto text = wss.str().c_str();
	RECT _rt{ 0,0,200,200 };

	Ellipse(_DC, h_x - 5, h_y - 5, h_x + 5, h_y + 5);

	DrawText(_DC, text, wss.str().size(), &_rt, DT_CENTER);
}

void CPlayer::Release()
{

}

void CPlayer::jump()
{
	jump_start_pos_y = Get_Info().fY;
	sx = Get_Info().fX;
	sy = Get_Info().fY;

	bJump = true;

	jump_dir_x = cos(3.141592f / 180.f * m_fAngle);
	jump_dir_y  = sin(3.141592f / 180.f * m_fAngle);

	float high_t = m_fForce* jump_dir_y / 9.8f;

	h_x = sx+m_fForce * jump_dir_x* high_t;
	h_y = sy+m_fForce * -jump_dir_y * high_t + 0.5f * 9.8f * (high_t * high_t);

	int a = 0;
}

CObj* CPlayer::Create_Shield()
{
	CObj* pObj = CAbstractFactory<CShield>::Create(this);
	return pObj;
}
