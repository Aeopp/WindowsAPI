#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
	: m_eDir(BULLET::END)
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.iCX = 33;
	m_tInfo.iCY = 33;

	m_fSpeed = 222.f;


}
void CBullet::calc()
{
	ht = m_fSpeed * sinf(m_fAngle * PI / 180.f) / 100.0f;


	hx =  sx+m_fSpeed* cosf(m_fAngle * PI / 180.f)* ht;
	hy = sy+m_fSpeed * -sinf(m_fAngle * PI / 180.f) * ht + 0.5 * 100.f * (ht * ht);

}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	t += 0.016f;

	sx;
	sy;

	float x = cosf(m_fAngle * PI / 180.f);
	float y = sinf(m_fAngle * PI / 180.f);

	m_tInfo.fX = sx+ m_fSpeed * x * t;
	m_tInfo.fY = sy + m_fSpeed * -y * t + 0.5f * (100.0f) * (t * t);


	/*m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;*/
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	/*if(100 >= m_tRect.left || 100 >= m_tRect.top
		|| WINCX - 100 <= m_tRect.right || WINCY - 100 <= m_tRect.bottom)
		m_bDead = true;*/
}

void CBullet::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	Rectangle(_DC, hx-5, hy-5, hx+5, hy+5);
}

void CBullet::Release()
{
}

