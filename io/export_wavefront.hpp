//@	{
//@	 "targets":[{"name":"export_wavefront.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"export_wavefront.o","rel":"implementation"}]
//@	}

#ifndef CITYPLAN_EXPORTWAVEFRONT_HPP
#define CITYPLAN_EXPORTWAVEFRONT_HPP

#include "file_deleter.hpp"

#include "geom/rectangle.hpp"

#include <cstdio>
#include <memory>

namespace Cityplan
	{
	void exportWavefront(Rectangle const* begin, Rectangle const* end, FILE* f);

	inline void exportWavefront(Rectangle const* begin, Rectangle const* end, char const* filename)
		{
		std::unique_ptr<FILE, FileDeleter> src{fopen(filename, "wb")};
		if(src == nullptr)
			{return;}
		return exportWavefront(begin, end, src.get());
		}

	}
#endif