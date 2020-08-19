#include "math.h"
#include "pch.h"

// 전체 각으로부터 방향 리턴

 std::pair<float, float> math::dir_from_angle(const float degree)
{
	float _radian = degree_to_radian(degree);

	return  { std::cosf(_radian), std::sinf(_radian) };
}

 // 이미 존재하는 방향으로부터 새로 더할려는 앵글만큼 방향 회전시켜서 리턴

  std::pair<float, float> math::rotation_dir_to_add_angle(const std::pair<float, float> dir, const float degree)
 {
	 // 코코 - 싸싸
	 // 싸코 + 코싸
	 const auto _radian = math::degree_to_radian(degree);
	 const float b_cos = std::cosf(_radian);
	 const float b_sin = std::sinf(_radian);

	 return { dir.first * b_cos - dir.second * b_sin,
		 dir.second * b_cos + dir.first * b_sin };
 }

  bool math::collision_rect_to_rect(const RECT lhs, const RECT rhs)
  {
	  const float lhs_half_width = (lhs.right - lhs.left) / 2;
	  const float rhs_half_width = (rhs.right - rhs.left) / 2;

	  const float rects_width = std::pow(lhs_half_width + rhs_half_width,2);
	 const float  rects_distance_from_x = std::pow(rhs_half_width - lhs_half_width, 2);

	 const float lhs_half_height = (lhs.bottom- lhs.top) / 2;
	 const float rhs_half_height = (rhs.bottom - rhs.top) / 2;

	 const float rects_height= std::pow(lhs_half_height+ rhs_half_height, 2);
	 const float  rects_distance_from_y = std::pow(rhs_half_height - lhs_half_height, 2);

	 if (rects_distance_from_y < rects_height
		 && rects_distance_from_x < rects_width)
	 {
		 return true;
	 }

	  return false;
  }
