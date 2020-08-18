#pragma once
#include <memory>
#include <mutex>

template<typename SubType>
class singleton_interface abstract
{
public :
	virtual void render(HDC hdc)abstract;
	virtual void update()abstract;
	virtual void initialize()abstract;
	virtual void release()abstract;

public:
	[[nodiscard]] static SubType& instance()
	{
		static std::once_flag _flag;

		static std::shared_ptr<SubType> _instance{ nullptr };

		static auto make_instance =
			[](auto& _instance_ptr) {
			_instance_ptr = std::make_shared<SubType>();
		};

		std::call_once(_flag, make_instance, _instance);

		return *_instance.get();
	}
};
