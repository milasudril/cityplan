//@	{"targets":[{"name":"vec2.hpp","type":"include"}]}

#ifndef CITYPLAY_VEC2_HPP
#define CITYPLAY_VEC2_HPP

namespace Cityplan
	{
	using Vec2 __attribute__((vector_size(16))) = double;
	};

#endif