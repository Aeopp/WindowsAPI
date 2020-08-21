#pragma once

#ifndef __OBJ_H__
#define __OBJ_H__

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;

public:
	void Set_Pos(float _x, float _y) { m_tInfo.fX = _x; m_tInfo.fY = _y; }
	void Set_Dead() { m_bDead = true; }
	void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void Add_PosX(float _x) { m_tInfo.fX += _x; }
	void Add_PosY(float _y) { m_tInfo.fY += _y; }

	float fall_time{ 0.f };
public:
	const INFO& Get_Info() const { return m_tInfo; }
	const RECT& Get_Rect() const { return m_tRect; }

protected:
	void Update_Rect();

public:
	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	float		m_fSpeed;
	bool		m_bDead;
	float		m_fAngle;
	CObj*		m_pTarget;
};


#endif // !__OBJ_H__
