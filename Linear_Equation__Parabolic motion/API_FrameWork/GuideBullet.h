#pragma once

#ifndef __GUIDEBULLET_H__
#define __GUIDEBULLET_H__


#include "Obj.h"
class CGuideBullet : public CObj
{
public:
	CGuideBullet();
	virtual ~CGuideBullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__GUIDEBULLET_H__
