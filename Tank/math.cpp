#include "math.h"
#include "pch.h"

// ��ü �����κ��� ���� ����

 std::pair<float, float> math::dir_from_angle(const float degree)
{
	float _radian = degree_to_radian(degree);

	return  { std::cosf(_radian), std::sinf(_radian) };
}

 // �̹� �����ϴ� �������κ��� ���� ���ҷ��� �ޱ۸�ŭ ���� ȸ�����Ѽ� ����

  std::pair<float, float> math::rotation_dir_to_add_angle(const std::pair<float, float> dir, const float degree)
 {
	 // ���� - �ν�
	 // ���� + �ڽ�
	 const auto _radian = math::degree_to_radian(degree);
	 const float b_cos = std::cosf(_radian);
	 const float b_sin = std::sinf(_radian);

	 return { dir.first * b_cos - dir.second * b_sin,
		 dir.second * b_cos + dir.first * b_sin };
 }
