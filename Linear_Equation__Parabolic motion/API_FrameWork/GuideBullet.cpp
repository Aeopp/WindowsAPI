#include "stdafx.h"
#include "GuideBullet.h"
#include "ObjMgr.h"


CGuideBullet::CGuideBullet()
{
}


CGuideBullet::~CGuideBullet()
{
	Release();
}

void CGuideBullet::Initialize()
{
	m_tInfo.iCX = 20;
	m_tInfo.iCY = 20;

	m_fSpeed = 10.f;
}

int CGuideBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	CObj* pTarget = CObjMgr::Get_Instance()->Get_Target(this, OBJID::MONSTER);

	if (pTarget)
	{
		float	fX = pTarget->Get_Info().fX - m_tInfo.fX;
		float	fY = pTarget->Get_Info().fY - m_tInfo.fY;
		float	fDia = sqrtf(fX * fX + fY * fY);

		float	fRad = acosf(fX / fDia);

		m_fAngle = fRad * 180.f / PI;

		if (m_tInfo.fY < pTarget->Get_Info().fY)
			m_fAngle *= -1.f;
	}

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CGuideBullet::Late_Update()
{
	if (100 >= m_tRect.left || 100 >= m_tRect.top
		|| WINCX - 100 <= m_tRect.right || WINCY - 100 <= m_tRect.bottom)
		m_bDead = true;
}

void CGuideBullet::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CGuideBullet::Release()
{
}
