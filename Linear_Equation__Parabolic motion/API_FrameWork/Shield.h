#pragma once

#ifndef __SHIELD_H__
#define __SHIELD_H__


#include "Obj.h"
class CShield : public CObj
{
public:
	CShield();
	virtual ~CShield();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	float		m_fDis;
};


#endif // !__SHIELD_H__