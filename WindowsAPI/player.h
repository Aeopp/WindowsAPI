#include "..\Tank\player.h"
#include "..\Tank\player.h"
#include "..\Tank\player.h"
#pragma once
#include "DrawObject.h"
#include <cmath>
#include "math.h"




namespace global
{
	void Fire(const float, const float, const float, const float, const float, const float);
}

template<typename DrawType>
class player :
    public DrawObject< DrawType>
{
public:
    using super = DrawObject<DrawType>;
    player();
public:
    virtual void Draw(HDC hdc)const& override;
    virtual void initialize()&;
private:
	std::pair<float, float> barrel_dir{};
    float barrel_length{ 75.0f };
    float barrel_angle{ 0.0f };
public:
    inline const std::pair<float, float>& get_barrel_dir()const&
    {
        return barrel_dir;
    }
    inline void set_barrel_dir(decltype(barrel_dir) pos)&noexcept
    {
        barrel_dir = std::move_if_noexcept(pos); 
    }
    inline  float get_barrel_length()const& noexcept
    {
        return barrel_length;
    }
    inline  float get_barrel_angle()const& noexcept
    {
        return barrel_angle;
    };
	inline  void set_barrel_angle(const float barrel_angle)& noexcept
	{
        this->barrel_angle = barrel_angle; 
	};
    void add_barrel_angle(const float radian) & noexcept;
    void move_from_barrel_dir(const bool bForward) & noexcept;
    void fire_from_barrel()const& noexcept;
public:
    virtual void Update()override;
};

template<typename DrawType>
 player<DrawType>::player()
{
     initialize();
}

template<typename DrawType>
void player<DrawType>::Draw(HDC hdc) const&
{
    super::Draw(hdc);
    const auto [x, y] = super::get_center();
    MoveToEx(hdc, x, y, nullptr);

    const auto [dir_x,dir_y] = get_barrel_dir();

    LineTo(hdc, x + dir_x*barrel_length, y +  dir_y * barrel_length);

};

inline void player::update()
{
}

inline void player::render()
{
}

template<typename DrawType>
void player<DrawType>::initialize()&
{
    super::set_center(500.0f, 500.0f);
    super::set_length(50.0f);
    set_barrel_dir({ 1,1 });
}
inline void player::release()
{
}
;

template<typename DrawType>
void player<DrawType>::add_barrel_angle(const float radian) & noexcept
{
    float alpha_angle = get_barrel_angle();

	const float _x_dir = barrel_dir.first;
	const float _y_dir = barrel_dir.second;

	/*barrel_dir.first = _x_dir * std::cosf(radian) - _y_dir * std::sinf(radian);
	barrel_dir.second = _y_dir * std::cosf(radian) + _x_dir * std::sinf(radian);

	set_barrel_angle(alpha_angle + radian);*/

	set_barrel_dir(
		{
			(_x_dir * std::cosf(radian)
			- _y_dir * std::sinf(radian)),

	(_y_dir * std::cosf(radian)
		+ _x_dir* std::sinf(radian))
		});

	set_barrel_angle(alpha_angle + radian);

#pragma region Procedure
    {
		/*set_barrel_dir(
			{
				(std::cosf(alpha_angle) * std::cosf(radian)
				- std::sinf(alpha_angle) * std::sinf(radian)),

		(std::sinf(alpha_angle) * std::cosf(radian)
			+ std::cosf(alpha_angle) * std::sinf(radian))
			});

		set_barrel_angle(alpha_angle + radian);*/
    }
#pragma endregion Procedure

};

template<typename DrawType>
 void player<DrawType>::move_from_barrel_dir(const bool bForward) & noexcept
{
     const auto[x,y] = get_barrel_dir();
     // 지워주세요. 
     static constexpr float temp_speed = 10.0f;
     if(bForward)
         super::move(x*temp_speed, y* temp_speed);
     else 
         super::move(x * temp_speed *-1.f, y * temp_speed* -1.f);
}

 template<typename DrawType>
 void player<DrawType>::fire_from_barrel() const& noexcept
 {
	//const float x,
	//	 const float y,
	//	 const float lenzgth,
	//	 const float dir_x,
	//	 const float dir_y,
	//	 const float speed)
     const auto _center = super::get_center();
     const auto [dir_x,dir_y ]  = get_barrel_dir();
     const float _barrel_length = get_barrel_length();

     global::Fire(_center.first + dir_x*_barrel_length, _center.second+ dir_y * _barrel_length,
          25.0f, dir_x, dir_y,10.0f);
 }

template<typename DrawType>
 void player<DrawType>::Update()
{
     super::Update();
};
