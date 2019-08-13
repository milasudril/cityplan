//@	{
//@	 "targets":[{"name":"export_wavefront.o","type":"object"}]
//@	}

#include "./export_wavefront.hpp"

#include <algorithm>
#include <cmath>

namespace
	{
	struct Vertex
		{
		double x;
		double y;
		double z;
		};

	struct Quad
		{
		std::array<int, 4> v_index;
		};

	struct Octmesh
		{
		std::array<Vertex, 8> verts;
		static constexpr std::array<Quad, 6> v_index
			{
			Quad{3, 2, 1, 0}
			,Quad{4, 5, 6, 7}
			,Quad{0, 1, 5, 4}
			,Quad{1, 2, 6, 5}
			,Quad{2, 3, 7, 6}
			,Quad{3, 0, 4, 7}
			};
		};

	constexpr std::array<Quad, 6> Octmesh::v_index;

	Octmesh makeBox(Cityplan::Rectangle const& r, double h_max, double margin)
		{
		auto h = std::min(sqrt(area(r)), h_max);
		auto d_half = Cityplan::Vec2{0.5, 0.5}*r.dimension();
		auto pos = r.position();
		Octmesh ret
			{
			 Vertex{pos.x() - d_half.width() + margin, pos.y() - d_half.height() + margin, -h}
			,Vertex{pos.x() + d_half.width() - margin, pos.y() - d_half.height() + margin, -h}
			,Vertex{pos.x() + d_half.width() - margin, pos.y() + d_half.height() - margin, -h}
			,Vertex{pos.x() - d_half.width() + margin, pos.y() + d_half.height() - margin, -h}
			,Vertex{pos.x() - d_half.width() + margin, pos.y() - d_half.height() + margin, h}
			,Vertex{pos.x() + d_half.width() - margin, pos.y() - d_half.height() + margin, h}
			,Vertex{pos.x() + d_half.width() - margin, pos.y() + d_half.height() - margin, h}
			,Vertex{pos.x() - d_half.width() + margin, pos.y() + d_half.height() - margin, h}
			};

		return ret;
		}
	}

namespace Cityplan
	{

	void exportWavefront(Rectangle const* begin, Rectangle const* end, FILE* output)
		{
		fprintf(output, "o BlockMask\n");
		std::for_each(begin, end, [output, k=0](auto const& rect) mutable
			{
			auto mesh = makeBox(rect, 20, 5);
			std::for_each(std::begin(mesh.verts), std::end(mesh.verts), [output](Vertex const& v)
				{fprintf(output, "v %.15g %.15g %.15g\n", v.x, v.y, v.z);});

			std::for_each(std::begin(mesh.v_index), std::end(mesh.v_index), [output, k](auto const& f)
				{fprintf(output, "f %d %d %d %d\n", f.v_index[0] + 1 + 8*k, f.v_index[1] + 1 + 8*k, f.v_index[2] + 1 + 8*k, f.v_index[3] + 1 + 8*k);});
			++k;
			});
		}
	}
