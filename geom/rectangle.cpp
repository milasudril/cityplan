//@	{"targets":[{"name":"rectangle.o","type":"object"}]}

#include "./rectangle.hpp"

#include <utility>
#include <exception>

namespace Cityplan
	{
	std::pair<Rectangle, Rectangle> split(Rectangle const& r, SplitDirection dir)
		{
		switch(dir)
			{
			case SplitDirection::Vertical:
				{
				auto dim_new = r.dimension() * Vec2{0.5, 1};

				auto pos_top = r.position() - Vec2{0.5, 0.0};
				auto pos_bottom = r.position() + Vec2{0.5, 0.0};

				return std::make_pair(Rectangle{pos_top, dim_new},Rectangle{pos_bottom, dim_new});
				}

			case SplitDirection::Horizontal:
				{
				auto dim_new = r.dimension() * Vec2{1.0, 0.5};

				auto pos_top = r.position() - Vec2{0.0, 0.5};
				auto pos_bottom = r.position() + Vec2{0.0, 0.5};

				return std::make_pair(Rectangle{pos_top, dim_new},Rectangle{pos_bottom, dim_new});
				}

			default:
				std::terminate();
			}
		}
	}
