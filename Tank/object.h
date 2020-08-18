#pragma once
#include <utility>
#include <functional>
#include "render_type.h"
#include "layer_type.h"

class object abstract
{
public:
	virtual void update();
	virtual void render(HDC hdc);
	virtual void initialize();
	virtual void release();
public:
	virtual uint32_t get_layer_id()const&;
private:
	std::pair<float, float> _location{};
	std::pair<float, float> _size{};
	std::weak_ptr<class object> _ptr{};
	render_type _render_type_id{render_type::rect};
	std::shared_ptr<class object> _owner{ nullptr };
	float _angle{ 0.0f };
	float _angle_speed{ 1.0f };
	bool bCollision{ true };
	GETSET(bool,_b_update_location_from_owner);
	std::pair<float, float> _distance_from_owner;
public:
	inline const auto& get_distance_from_owner()const&;
	inline void set_distance_from_owner(decltype(_distance_from_owner) _distance_from_owner)&;
	inline const auto& get_angle_speed()const&;
	inline void set_angle_speed(decltype(_angle_speed) _angle_speed)&;
	inline const auto& get_angle()const&;
	inline void set_angle(decltype(_angle) _angle)&;
	inline const auto& get_ptr()const&;
	inline void set_ptr(const std::shared_ptr<object>& _ptr)&;
	inline const auto& get_location()const&;
	inline void set_location(decltype(_location) _location)&;
	inline const auto& get_size()const&;
	inline void set_size(decltype(_size) _size)&;
	inline void set_render_type(decltype(_render_type_id) _render_type_id)&;;
	inline void set_owner(decltype(_owner) _owner)&;
	inline const auto& get_owner()const&;
};

inline const auto& object::get_distance_from_owner() const&
{
	return _distance_from_owner;
}

inline void object::set_distance_from_owner(decltype(_distance_from_owner) _distance_from_owner)&
{
	this->_distance_from_owner = _distance_from_owner;
}

inline const auto& object::get_angle_speed() const&
{
	return _angle_speed;
};

inline void object::set_angle_speed(decltype(_angle_speed) _angle_speed)&
{
	this->_angle_speed = std::move(_angle_speed); 
};

inline const auto& object::get_angle() const&
{
	return _angle;
};

inline void object::set_angle(decltype(_angle) _angle)&
{
	this->_angle = std::move(_angle);
};

inline const auto& object::get_ptr() const&
{
	return _ptr;
};

inline void object::set_ptr(const std::shared_ptr<object>& _ptr)&
{
	this->_ptr = _ptr;
};

inline const auto& object::get_location() const&
{
	return _location;
};

inline void object::set_location(decltype(_location) _location)&
{
	this->_location = std::move(_location);
};

inline const auto& object::get_size() const&
{
	return _size;
};

inline void object::set_size(decltype(_size) _size)&
{
	this->_size = std::move(_size);
};

inline void object::set_render_type(decltype(_render_type_id) _render_type_id)&
{
	this->_render_type_id = _render_type_id;
};

inline void object::set_owner(decltype(_owner) _owner)&
{
	this->_owner = std::move(_owner);
};

inline const auto& object::get_owner() const&
{
	return _owner;
}
