#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "CollisionMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& iter = m_listObj[i].begin(); iter != m_listObj[i].end(); )
		{
   			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				SAFE_DELETE(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}

	//CCollisionMgr::Collision_Rect(m_listObj[OBJID::MONSTER], m_listObj[OBJID::MOUSE]);
	//CCollisionMgr::Collision_Sphere(m_listObj[OBJID::MONSTER], m_listObj[OBJID::MOUSE]);
	CCollisionMgr::Collision_Rect(m_listObj[OBJID::BULLET], m_listObj[OBJID::MONSTER]);
	CCollisionMgr::Collision_SegmentSphere(m_listObj[OBJID::SEGMENT],m_listObj[OBJID::PLAYER]);
	//CCollisionMgr::Collision_RectEx(m_listObj[OBJID::PLAYER], m_listObj[OBJID::MONSTER]);
	//CCollisionMgr::Collision_RectEx(m_listObj[OBJID::MONSTER], m_listObj[OBJID::PLAYER]);
}

void CObjMgr::Late_Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
			pObj->Late_Update();
	}
}

void CObjMgr::Render(HDC _DC)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
			pObj->Render(_DC);
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*>);
		m_listObj[i].clear();
	}
}

CObj* CObjMgr::Get_Target(CObj* _Dst, OBJID::ID _eID)
{
	CObj*	pTarget = nullptr;
	float	fDis = 0.f;

	for (auto& pObj : m_listObj[_eID])
	{
		float	fX = pObj->Get_Info().fX - _Dst->Get_Info().fX;
		float	fY = pObj->Get_Info().fY - _Dst->Get_Info().fY;
		float	fDia = sqrtf(fX * fX + fY * fY);

		if (fDia < fDis || !fDis)
		{
			fDis = fDia;
			pTarget = pObj;
		}
	}

	return pTarget;
}
