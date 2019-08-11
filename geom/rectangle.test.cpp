//@	{"targets":[{"name":"rectangle.test","type":"application", "autorun":1}]}

#undef NDEBUG

#include "rectangle.hpp"

#include <cassert>
#include <cstdio>
#include <cstdlib>

namespace Test
	{
	void cityplanRectangleSplitVertical()
		{
		Cityplan::Rectangle a{Cityplan::Position{}.x(0).y(0), Cityplan::Dimension{}.width(1).height(1)};

		auto res = split(a, Cityplan::SplitDirection::Vertical);
		assert(width(res.first) == 0.5 * width(a));
		assert(height(res.first) == height(a));
		assert(width(res.first) == width(res.second));
		assert(height(res.first) == height(res.second));

		assert(std::abs(res.first.position().x()) == 0.5);
		assert(res.first.position().x() == -res.second.position().x());
		assert(res.first.position().y() == 0);
		assert(res.second.position().y() == 0);
		}

	void cityplanRectangleSplitHorizontal()
		{
		Cityplan::Rectangle a{Cityplan::Position{}.x(0).y(0), Cityplan::Dimension{}.width(1).height(1)};

		auto res = split(a, Cityplan::SplitDirection::Horizontal);
		assert(height(res.first) == 0.5 * height(a));
		assert(width(res.first) == width(a));
		assert(height(res.first) == height(res.second));
		assert(width(res.first) == width(res.second));

		assert(std::abs(res.first.position().y()) == 0.5);
		assert(res.first.position().y() == -res.second.position().y());
		assert(res.first.position().x() == 0);
		assert(res.second.position().x() == 0);
		}
	}

int main()
	{Test::cityplanRectangleSplitVertical();}
