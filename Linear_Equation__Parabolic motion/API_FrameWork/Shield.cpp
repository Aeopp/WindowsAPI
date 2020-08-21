#include "stdafx.h"
#include "Shield.h"


CShield::CShield()
	: m_fDis(0.f)
{
}


CShield::~CShield()
{
	Release();
}

void CShield::Initialize()
{
	m_tInfo.iCX = 30;
	m_tInfo.iCY = 30;

	m_fSpeed = 10.f;
	m_fDis = 100.f;
}

int CShield::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fAngle += m_fSpeed;

	m_tInfo.fX = m_pTarget->Get_Info().fX + cosf(m_fAngle * PI / 180.f) * m_fDis;
	m_tInfo.fY = m_pTarget->Get_Info().fY - sinf(m_fAngle * PI / 180.f) * m_fDis;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CShield::Late_Update()
{
	if (100 >= m_tRect.left || 100 >= m_tRect.top
		|| WINCX - 100 <= m_tRect.right || WINCY - 100 <= m_tRect.bottom)
		m_bDead = true;
}

void CShield::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CShield::Release()
{
}
