#pragma once
#include <numeric>
#include <numbers>
#include <cmath>

class math
{
public:
	static inline constexpr float degree_to_radian(const float degree)
	{
		constexpr float  factor = (float)std::numbers::pi / (float)180.0f;

		return factor * degree;
	};
	static inline constexpr float radian_to_degree(const float radian)
	{
		constexpr float factor = 180.0f / (float)std::numbers::pi;

		return factor * radian;
	};
	// ��ü �����κ��� ���� ����
	static std::pair<float, float> dir_from_angle(const float degree);;
	// �̹� �����ϴ� �������κ��� ���� ���ҷ��� �ޱ۸�ŭ ���� ȸ�����Ѽ� ����
	static std::pair<float, float> rotation_dir_to_add_angle(const std::pair<float, float> dir,
		const float degree);
};



template<typename T>
T operator+(const T& lhs, const T& rhs)
{
	const auto& [x, y] = lhs;
	const auto& [x1, y1] = rhs;
	return T{ x + x1,y + y1 };
};
template<typename T>
T operator-(const T& lhs, const T& rhs)
{
	const auto& [x, y] = lhs;
	const auto& [x1, y1] = rhs;
	return T{ x - x1,y - y1 };
};
template<typename T>
T operator*(const T& lhs, const T& rhs)
{
	const auto& [x, y] = lhs;
	const auto& [x1, y1] = rhs;
	return T{ x * x1,y * y1 };
};

template<typename T>
T operator/(const T& lhs, const T& rhs)
{
	const auto& [x, y] = lhs;
	const auto& [x1, y1] = rhs;
	return T{ x / x1,y / y1 };
};

