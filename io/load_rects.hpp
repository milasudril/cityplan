//@	{
//@	 "targets":[{"name":"load_rects.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"load_rects.o","rel":"implementation"}]
//@	}

#ifndef CITYPLAY_LOAD_RECTS_HPP
#define CITYPLAY_LOAD_RECTS_HPP

#include "geom/rectangle.hpp"

#include <vector>
#include <cstdio>

namespace Cityplan
	{
	std::vector<Rectangle> loadRects(FILE* src);
	}

#endif
