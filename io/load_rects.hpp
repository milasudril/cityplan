//@	{
//@	 "targets":[{"name":"load_rects.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"load_rects.o","rel":"implementation"}]
//@	}

#ifndef CITYPLAY_LOAD_RECTS_HPP
#define CITYPLAY_LOAD_RECTS_HPP

#include "geom/rectangle.hpp"

#include <vector>
#include <cstdio>
#include <memory>

namespace Cityplan
	{
	std::vector<Rectangle> loadRects(FILE* src);

	namespace detail
		{
		struct FileDeleter
			{
			void operator()(FILE* f)
				{fclose(f);}
			};
		}

	inline std::vector<Rectangle> loadRects(char const* filename)
		{
		std::unique_ptr<FILE, detail::FileDeleter> src{fopen(filename, "rb")};
		if(src == nullptr)
			{return std::vector<Rectangle>{};}
		return loadRects(src.get());
		}
	}

#endif
