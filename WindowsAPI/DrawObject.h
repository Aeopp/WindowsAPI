#pragma once
#include <type_traits>
#include <Windows.h>
#include <utility>
struct draw_rect {};
struct draw_circle {};

template<typename DrawType>
class DrawObject
{
private:
	float center_x= 0.0f;
	float center_y = 0.0f;
	float length{};
public :
	DrawObject(const float init_x, const float init_y,
		const float init_length)
		:
		center_x{ init_x },
		center_y{ init_y },
	    length { init_length }
	{};
	DrawObject(const DrawObject& ) = default;
	DrawObject(DrawObject&& Rhs) noexcept = default ;
	DrawObject& operator=(const DrawObject& Rhs) 
	{
		if (&Rhs == this)
		{
			return *this;
		}
		center_x = Rhs.center_x;
		center_y = Rhs.center_y;
		length = Rhs.length;

		return *this;
	};

	DrawObject& operator=(DrawObject&&) noexcept = default;

	DrawObject() = default;
	virtual ~DrawObject() noexcept = default;
public:
	inline std::pair<float,float> get_center()const&
	{
		return { center_x,center_y };
	}
	inline float get_length()const&
	{
		return length;
	}
	virtual void Draw(HDC hdc)const&
	{
	/*	SetPixel(hdc, center_x, center_y, COLORREF(0xff00ff));
		SetPixel(hdc, center_x+1, center_y+1, COLORREF(0xff00ff));*/

		if constexpr (std::is_same_v<DrawType, draw_rect>)
		{
			Rectangle(hdc, center_x - length, center_y - length, center_x + length, center_y + length);
		}
		else if constexpr (std::is_same_v<DrawType, draw_circle>)
		{
			Ellipse(hdc, center_x - length, center_y - length, center_x + length, center_y + length);
		}
	}
	RECT get_rect()const&;

	void Move(const float x, const float y)&
	{
		center_x += x;
		center_y += y;
	}

	virtual void Update();

public:
	void set_center(const decltype(center_x) x, const decltype(center_y) y) & noexcept;
	void set_length(const float length) & noexcept;
};

template<typename DrawType>
 RECT DrawObject<DrawType>::get_rect() const&
{
	 using RECT_variable_type = LONG;

	 return RECT{ 
		 LONG(center_x - length), 
			  LONG(center_y - length),
			  LONG(center_x + length),
			  LONG(center_y + length) };
}

template<typename DrawType>
void DrawObject<DrawType>::Update()
{

}
template<typename DrawType>
void DrawObject<DrawType>::set_center(const decltype(center_x) x, const decltype(center_y) y) & noexcept
{
	center_x = x;
	center_y = y;
};

template<typename DrawType>
void DrawObject<DrawType>::set_length(const float length) & noexcept
{
	this->length = length; 
};

