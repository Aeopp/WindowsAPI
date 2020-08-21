#include "stdafx.h"
#include "ScrewBullet.h"


CScrewBullet::CScrewBullet()
	: m_fCenterSpeed(0.f), m_fCenterAngle(0.f), m_fDis(0.f), m_bStart(true)
{
	ZeroMemory(&m_tCenterPos, sizeof(m_tCenterPos));
}


CScrewBullet::~CScrewBullet()
{
	Release();
}

void CScrewBullet::Initialize()
{
	m_tInfo.iCX = 10;
	m_tInfo.iCY = 10;
	
	m_fSpeed = 30.f;
	m_fCenterSpeed = 5.f;
	m_fDis = 30.f;
}

int CScrewBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	
	if (m_bStart)
	{
		m_tCenterPos.x = (LONG)m_tInfo.fX;
		m_tCenterPos.y = (LONG)m_tInfo.fY;
		m_fCenterAngle = m_fAngle;
		m_bStart = false;
	}

	m_fAngle += m_fSpeed;

	m_tCenterPos.x += (LONG)(cosf(m_fCenterAngle * PI / 180.f) * m_fCenterSpeed);
	m_tCenterPos.y -= (LONG)(sinf(m_fCenterAngle * PI / 180.f) * m_fCenterSpeed);

	m_tInfo.fX = m_tCenterPos.x + cosf(m_fAngle * PI / 180.f) * m_fDis;
	m_tInfo.fY = m_tCenterPos.y - sinf(m_fAngle * PI / 180.f) * m_fDis;


	Update_Rect();
	return OBJ_NOEVENT;
}

void CScrewBullet::Late_Update()
{
	if (100 >= m_tRect.left || 100 >= m_tRect.top
		|| WINCX - 100 <= m_tRect.right || WINCY - 100 <= m_tRect.bottom)
		m_bDead = true;
}

void CScrewBullet::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CScrewBullet::Release()
{
}
