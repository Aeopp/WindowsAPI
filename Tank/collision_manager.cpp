#include "pch.h"
#include "collision_manager.h"
#include "object.h"
#include "math.h"


void collision_manager::collision_beetween_objects(
	const std::list<std::shared_ptr<class object>>& lhs, 
	const std::list<std::shared_ptr<class object>>& rhs) const&
{
	for (auto& src: lhs)
	{
		const RECT _src_rect = src->get_collision_rect();
		for (auto& dest: rhs)
		{
			// °°Àº °´Ã¼ÀÓ
			if (&(*src) == &(*dest))
			{
				continue;
			}

			const RECT _dest_rect = dest->get_collision_rect();

			bool bCollision = math::collision_rect_to_rect(_src_rect, _dest_rect);

			if (bCollision)
			{
				src->Hit(dest);
				dest->Hit(dest);
			}
			else
			{

			}
		}
	}
}
