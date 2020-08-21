#pragma once

#ifndef __ABSTRACTFACTORY_H__
#define __ABSTRACTFACTORY_H__

class CObj;

template <typename T>
class CAbstractFactory
{
public:
	static T* Create()
	{
		T* pObj = new T;
		pObj->Initialize();

		return pObj;
	}
	static T* Create(float _x, float _y)
	{
		T* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);

		return pObj;
	}
	static T* Create(float _x, float _y, float _Angle)
	{
		T* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);
		pObj->Set_Angle(_Angle);

		return pObj;
	}
	static T* Create(CObj* _pTarget)
	{
		T* pObj = new T;
		pObj->Initialize();
		pObj->Set_Target(_pTarget);

		return pObj;
	}
};

#endif // !__ABSTRACTFACTORY_H__
