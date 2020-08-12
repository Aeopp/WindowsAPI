#pragma once

#include "DrawObject.h"
#include "WindowsAPI.h"

template<typename DrawType>
class Bullet : public DrawObject<DrawType>
{
private:
	using super = DrawObject<DrawType>;
	float dir_x{};
	float dir_y{};
	bool bDie{ false };
public:
	Bullet(const float init_x, const float init_y,
		const float init_length,const float init_dir_x,const float init_dir_y)
		:
		DrawObject<DrawType>(init_x,init_y,init_length),
		dir_x{ init_dir_x },dir_y{init_dir_y}
	{};
	Bullet() = default; 
	
	Bullet(const Bullet&) = default;
	Bullet(Bullet&&) noexcept = default;

	Bullet& operator=(const Bullet& Rhs)
	{
		if (&Rhs == this)
		{
			return *this; 
		}
		super::operator=(Rhs);
		dir_x = Rhs.dir_x;
		dir_y = Rhs.dir_y;
		bDie = Rhs.bDie;

		return *this; 
	};

	Bullet& operator=(Bullet&&) noexcept = default;
public:
	void Update(HWND hwnd)&
	{
		super::Move(dir_x, dir_y);
		RECT _windowRECT = Bullet::get_bullet_fence();

		const auto [x,y]= super::get_center();
		const float _length = super::get_length();
		
		// 화면 밖을 넘어간 상태.
		if (x - _length > _windowRECT.right ||
			x + _length < _windowRECT.left ||
			y + _length < _windowRECT.top ||
			y - _length > _windowRECT.bottom)
		{
			bDie = true;
		}
	};

	inline bool IsDie()const& 
	{
		return bDie; 
	}

	// TODO :: 테스트 한뒤에 삭제하기
	 void destroy_draw(const  HDC hdc)
	{
		const wchar_t* destroy_message = L"  소멸 !! ";
		const auto [x,y] = super::get_center();
		const float _length = super::get_length();

		RECT _Rect{ x - _length
				,y - _length,
				x + _length,
				y + _length };

		// 소멸되었다는 메시지를 출력한다.
		DrawText(hdc, destroy_message,-1, &_Rect,
				DT_CENTER | DT_WORDBREAK);
	}
public:
	
		static RECT get_bullet_fence()
		{
			RECT _client_rect;

			GetClientRect(global::hWnd, &_client_rect);

			using uint32_t  = unsigned int;

			static constexpr uint32_t bullet_fence_size = 150;

			_client_rect.left += bullet_fence_size;

			_client_rect.top += bullet_fence_size;

			_client_rect.right -= bullet_fence_size;

			_client_rect.bottom -= bullet_fence_size;

			return _client_rect;
		}
		
		static void Draw_bullet_fence(const HDC hdc)
		{
			RECT bullet_fence = get_bullet_fence();

			Rectangle(hdc, bullet_fence.left, bullet_fence.top, bullet_fence.right, bullet_fence.bottom);
		}
};

 