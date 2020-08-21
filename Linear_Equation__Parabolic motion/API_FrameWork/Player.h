#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Obj.h"
#include "Bullet.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update();
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	float m_fForce;
	float jump_start_pos_y{};
	void jump();
	bool bJump = false;
	float t{ 0.f };

	float high_t{ 0.f };

	float jump_dir_x{ 0.f };
	float jump_dir_y{ 0.f };
	float dir_x = 1;
	float dir_y = 1;

	float h_x, h_y;

	float sx, sy;

private:
	CObj* Create_Shield();
private:
	template <typename T>
	CObj* Create_Bullet()
	{
		T* bullet= CAbstractFactory<T>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle);
		if constexpr (std::is_same_v<T, CBullet>)
		{
			bullet->sx = m_tPosin.x;
			bullet->sy = m_tPosin.y;
			bullet->calc();
		}
		
		return bullet;
	}

private:
	POINT			m_tPosin;
	float			m_fCannon;
};

#endif // !__PLAYER_H__
