#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "Monster.h"
#include "Mouse.h"
#include "CollisionMgr.h"
#include "Shield.h"
#include "ObjMgr.h"
#include "Line.h"
#include "timer.h"


CMainGame::CMainGame()
	:  m_dwTime(GetTickCount()), m_iFPS(0)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);

	CObj* pObj = CAbstractFactory<CPlayer>::Create();
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::PLAYER);
	pObj->Set_Pos(100, 0);

	auto _Line = CAbstractFactory<Line>::Create();
	CObjMgr::Get_Instance()->Add_Object(_Line, OBJID::SEGMENT);
	_Line->set_segment({ 0,550,200,550 });

	_Line = CAbstractFactory<Line>::Create();
	CObjMgr::Get_Instance()->Add_Object(_Line, OBJID::SEGMENT);
	_Line->set_segment({ 200,550,400,350 });

	_Line = CAbstractFactory<Line>::Create();
	CObjMgr::Get_Instance()->Add_Object(_Line, OBJID::SEGMENT);
	_Line->set_segment({ 400,350,600,350 });
};

void CMainGame::Update()
{
	++m_iFPS;
	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS: %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_dwTime = GetTickCount();
		m_iFPS = 0;
	}

	timer::Get_Instance()->dt = get_dt();

	CObjMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);

	CObjMgr::Get_Instance()->Render(m_DC);
}

void CMainGame::Release()
{
	CObjMgr::Destroy_Instance();
	timer::Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
};

float CMainGame::get_dt()
{
	return (float)m_dwTime * (1.f/1000.f);
}
