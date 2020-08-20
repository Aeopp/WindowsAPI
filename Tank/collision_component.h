#pragma once
#include "pch.h"

class collision_component
{
public:
	template<typename lhs_ty,typename size_ty>
	RECT get_collision_rect(const lhs_ty& lhs,const size_ty& rhs)const&;
};

template<typename lhs_ty, typename size_ty>
 RECT collision_component::get_collision_rect(const lhs_ty& lhs, const size_ty& rhs) const&
{
	 const auto& [x,y] = lhs;
	 const auto& [cx, cy] = rhs;
	 RECT _Rect;
	 _Rect.left = x;
	 _Rect.top = y;
	 _Rect.right = x + cx;
	 _Rect.bottom = y + cy;

	 return _Rect;
}
