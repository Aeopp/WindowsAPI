#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;
}

int CMouse::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	POINT		pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	//ShowCursor(FALSE);

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
}

void CMouse::Render(HDC _DC)
{
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMouse::Release()
{
}
