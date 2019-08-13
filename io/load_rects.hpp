//@	{
//@	 "targets":[{"name":"load_rects.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"load_rects.o","rel":"implementation"}]
//@	}

#ifndef CITYPLAY_LOAD_RECTS_HPP
#define CITYPLAY_LOAD_RECTS_HPP

#include "./file_deleter.hpp"

#include "geom/rectangle.hpp"

#include <vector>
#include <memory>

namespace Cityplan
	{
	std::vector<Rectangle> loadRects(FILE* src);

	inline std::vector<Rectangle> loadRects(char const* filename)
		{
		std::unique_ptr<FILE, FileDeleter> src{fopen(filename, "rb")};
		if(src == nullptr)
			{return std::vector<Rectangle>{};}
		return loadRects(src.get());
		}
	}

#endif
