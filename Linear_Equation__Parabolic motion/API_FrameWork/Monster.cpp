#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
	: m_pPlayer(nullptr)
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;

	m_fSpeed = 1.f;
}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	//float	fX = m_pPlayer->Get_Info().fX - m_tInfo.fX;
	//float	fY = m_pPlayer->Get_Info().fY - m_tInfo.fY;
	//float	fDia = sqrtf(fX * fX + fY * fY);

	//float	fRad = acosf(fX / fDia);

	////if (m_tInfo.fY < m_pPlayer->Get_Info().fY)
	////	fRad = 2 * PI - fRad;

	//m_fAngle = fRad * 180.f / PI;

	//if (m_tInfo.fY < m_pPlayer->Get_Info().fY)
	//	m_fAngle *= -1.f;
	//
	//m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	//m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;


	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{

}

void CMonster::Render(HDC _DC)
{
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release()
{
}
