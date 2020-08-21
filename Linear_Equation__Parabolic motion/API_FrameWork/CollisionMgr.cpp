#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "Line.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &Dst->Get_Rect(), &Src->Get_Rect()))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	float fX = 0.f, fY = 0.f;
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fX, &fY))
			{
				if (fX > fY)
				{
					if (Dst->Get_Info().fY < Src->Get_Info().fY)
						Src->Add_PosY(fY);
					else
						Src->Add_PosY(-fY);
				}
				else
				{
					if (Dst->Get_Info().fX < Src->Get_Info().fX)
						Src->Add_PosX(fX);
					else
						Src->Add_PosX(-fX);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_SegmentSphere(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	float fX = 0.f;
	float fY = 0.f;

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Segment_to_Sphere(dynamic_cast<Line*>(Dst), Src,&fX,&fY))
			{
				/*	Src->Add_PosX(fX);
					Src->Add_PosY(fY);*/
				// Src->fall_time = 0.0f;
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* _Dst, CObj* _Src)
{
	float fX = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float fY = _Dst->Get_Info().fY - _Src->Get_Info().fY;
	float fDia = sqrtf(fX * fX + fY * fY);

	float fRad = (float)((_Dst->Get_Info().iCX + _Src->Get_Info().iCX) >> 1);

	if (fRad > fDia)
		return true;
	return false;
}

bool CCollisionMgr::Check_Rect(CObj* _Dst, CObj* _Src, float* _x, float* _y)
{
	float fDisX = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float fDisY = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);

	float fCX = (float)((_Dst->Get_Info().iCX + _Src->Get_Info().iCX) >> 1);
	float fCY = (float)((_Dst->Get_Info().iCY + _Src->Get_Info().iCY) >> 1);

	if (fDisX <= fCX && fDisY <= fCY)
	{
		*_x = fCX - fDisX;
		*_y = fCY - fDisY;
		return true;
	}
	return false;
};


//bool does_line_segment_intersect_sphere(const vector3_type& line_segment_start,
//	const vector3_type& line_segment_end,
//	const vector3_type& sphere_center, float sphere_radius)
//{
//	vector3_type from_sphere_center_to_line_segment_start = line_segment_start - sphere_center;
//
//	float c = dot_product(from_sphere_center_to_line_segment_start,
//		from_sphere_center_to_line_segment_start) - sphere_radius * sphere_radius;
//
//	// 선분의 시작점부터 구의 중심까지의 거리가 구의 반지름보다 크지 않다면,
//	// 선분의 시작점이 구의 안에 있으므로 교차합니다.
//	if (c <= 0.0f)
//		return true;
//
//	vector3_type line_segment_direction = line_segment_end - line_segment_start;
//	float line_segment_length = line_segment_direction.length;
//	if (line_segment_length == 0.0f)
//		return false;
//	vector3_type normalized_line_segment_direction = line_segment_direction /
//		line_segment_length;
//	float b_prime = dot_product(from_sphere_center_to_line_segment_start,
//		normalized_line_segment_direction);
//
//	// 선분의 시작점이 구의 밖에 있고, 구의 중심에서 선분의 시작점을 향하는 벡터와 선분의 방향
//	// 벡터가 이루는 각이 90도 미만이라면 교차하지 않습니다.
//	if (b_prime > 0.0f)
//		return false;
//
//	// 원래는 b' * b' - a * c를 사용해야 합니다. 그런데 선분의 방향 벡터가 단위 벡터면,
//	// a는 dot_product(normalized_line_segment_direction, normalized_line_segment_direction) =
//	// 1이므로, a를 생략 가능합니다.
//	float square_root_of_discriminant = sqrt(b_prime * b_prime - c);
//
//	float t1 = -b_prime + square_root_of_discriminant;
//	if (t1 >= 0.0f && t1 <= line_segment_length)
//		return true;
//
//	float t2 = -b_prime - square_root_of_discriminant;
//	if (t2 >= 0.0f && t2 <= line_segment_length)
//		return true;
//}
bool CCollisionMgr::Check_Segment_to_Sphere(Line* _Dst, CObj* _Src, float* _x, float* _y)
{
	if (!_Dst || !_Src) return false;

	vec from_sphere_center_to_line_segment_start = vec{ _Dst->_segment.v0.x - _Src->Get_Info().fX , _Dst->_segment.v1.y - _Src->Get_Info().fY };

	float dot = ((from_sphere_center_to_line_segment_start.x * from_sphere_center_to_line_segment_start.x)
		+ (from_sphere_center_to_line_segment_start.y * from_sphere_center_to_line_segment_start.y)) - (_Src->Get_Info().iCX/2 * _Src->Get_Info().iCX/2);

	if (dot <= 0.0f)
		return true;

	vec seg_dir = _Dst->_segment.v1 - _Dst->_segment.v0;
	float line_segment_length = sqrtf(seg_dir.x * seg_dir.x + seg_dir.y * seg_dir.y);

	if (line_segment_length == 0.0f)
		return false;

	vec nor_seg_dir = {seg_dir.x / line_segment_length, seg_dir.y / line_segment_length };

	float b_prime = (from_sphere_center_to_line_segment_start.x * nor_seg_dir.x + from_sphere_center_to_line_segment_start.y * nor_seg_dir.y);


	if (b_prime > 0.0f)
		return false;

	float square_root_of_discriminant = sqrtf(b_prime * b_prime - dot);

	float t1 = -b_prime + square_root_of_discriminant;
	if (t1 >= 0.0f && t1 <= line_segment_length)
	{
		vec v0;
		v0.x = nor_seg_dir.x * b_prime + _Dst->_segment.v0.x;
		v0.y = nor_seg_dir.y * b_prime + _Dst->_segment.v0.y;

		*_x = _Src->Get_Info().fX - v0.x;
		*_y = _Src->Get_Info().fY - v0.y;

	
			MoveToEx(GetDC(g_hWnd), v0.x, v0.y, nullptr);
			LineTo(GetDC(g_hWnd), _Src->Get_Info().fX, _Src->Get_Info().fY);

		
		
		int i = 0;

		return true;
	}
		

	float t2 = -b_prime - square_root_of_discriminant;
	if (t2 >= 0.0f && t2 <= line_segment_length)
	{
		vec v0;
		v0.x = nor_seg_dir.x * b_prime + _Dst->_segment.v0.x;
		v0.y = nor_seg_dir.y * b_prime + _Dst->_segment.v0.y;

		*_x = _Src->Get_Info().fX - v0.x;
		*_y = _Src->Get_Info().fY - v0.y;

		int i = 0;

		return true;
	}
		
}
