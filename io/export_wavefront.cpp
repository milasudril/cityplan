//@	{
//@	 "targets":[{"name":"export_wavefront.o","type":"object"}]
//@	}

#include "./export_wavefront.hpp"

#include <algorithm>
#include <vector>

using namespace Cityplan;

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

	Octmesh makeBox(std::array<Position, 4> const& face, double h)
		{
		Octmesh ret
			{
			 Vertex{face[0].x(), face[0].y(), -h}
			,Vertex{face[1].x(), face[1].y(), -h}
 			,Vertex{face[2].x(), face[2].y(), -h}
 			,Vertex{face[3].x(), face[3].y(), -h}
			,Vertex{face[0].x(), face[0].y(),  h}
			,Vertex{face[1].x(), face[1].y(),  h}
 			,Vertex{face[2].x(), face[2].y(),  h}
 			,Vertex{face[3].x(), face[3].y(),  h}
			};

		return ret;
		}

	std::vector<std::array<Position, 4>> generateBlocks(Rectangle const* begin, Rectangle const* end, double offset)
		{
		std::vector<std::array<Position, 4>> ret;
		std::transform(begin, end, std::back_inserter(ret),[offset](auto const& rect)
			{
			auto d_half = Vec2{0.5, 0.5}*(rect.dimension().offsetVector() + Vec2{offset, offset});
			auto pos = rect.position();
			auto min = pos - d_half;
			auto max = pos + d_half;
			return std::array<Position, 4>
				{
				 min
				,Position{}.x(max.x()).y(min.y())
				,max
				,Position{}.x(min.x()).y(max.y())
				};
			});
		return ret;
		}

	std::vector<std::array<Position, 8>> generateCrosspoints(Rectangle const* begin, Rectangle const* end
		, double offset_inner, double offset_outer)
		{
		std::vector<std::array<Position, 8>> ret;
		std::transform(begin, end, std::back_inserter(ret),[offset_inner, offset_outer](auto const& rect)
			{
			auto d_half_inner = Vec2{0.5, 0.5}*(rect.dimension().offsetVector() - Vec2{offset_inner, offset_inner});
			auto d_half_outer = Vec2{0.5, 0.5}*(rect.dimension().offsetVector() + Vec2{offset_outer, offset_outer});
			auto pos = rect.position();
			auto min_inner = pos - d_half_inner;
			auto max_inner = pos + d_half_inner;
			auto min_outer = pos - d_half_outer;
			auto max_outer = pos + d_half_outer;
			return std::array<Position, 8>
				{
				 Position{}.x(min_outer.x()).y(min_inner.y())
				,Position{}.x(min_inner.x()).y(min_outer.y())
				,Position{}.x(max_inner.x()).y(min_outer.y())
				,Position{}.x(max_outer.x()).y(min_inner.y())
				,Position{}.x(max_outer.x()).y(max_inner.y())
				,Position{}.x(max_inner.x()).y(max_outer.y())
				,Position{}.x(min_inner.x()).y(max_outer.y())
				,Position{}.x(min_outer.x()).y(max_inner.y())
				};
			});
		return ret;
		}
	}

void Cityplan::exportWavefront(Rectangle const* a, Rectangle const* b, FILE* output)
	{
	auto blocks_inner = generateBlocks(a, b, -9.0);
	auto blocks_outer = generateBlocks(a, b, +9.0);
	auto blocks_mid = generateBlocks(a, b, 0);
	auto blocks_crosspoints = generateCrosspoints(a, b, 9, 0);

	fprintf(output, "o BlockMask\n");
	for(size_t k = 0; k < blocks_inner.size(); ++k)
		{
		auto mesh = makeBox(blocks_inner[k], 100);
		std::for_each(std::begin(mesh.verts), std::end(mesh.verts), [output](Vertex const& v)
			{fprintf(output, "v %.15g %.15g %.15g\n", v.x, v.y, v.z);});

		std::for_each(std::begin(mesh.v_index), std::end(mesh.v_index), [output, k](auto const& f)
			{
			fprintf(output, "f %zu %zu %zu %zu\n"
				, f.v_index[0] + 1 + 8*k
				, f.v_index[1] + 1 + 8*k
				, f.v_index[2] + 1 + 8*k
				, f.v_index[3] + 1 + 8*k);
			});
		}

	fprintf(output, "o Streets\n");
	for(size_t k = 0; k < blocks_inner.size(); ++k)
		{
		auto const& inner = blocks_inner[k];
		auto const& outer = blocks_mid[k];
		auto const& cross_points = blocks_crosspoints[k];

		constexpr auto faces = std::array<Quad, 8>
			{
			 Quad{0,  8,  4,  9}
			,Quad{0,  9, 10,  1}
			,Quad{1, 10,  5, 11}
			,Quad{1, 11, 12,  2}
			,Quad{2, 12,  6, 13}
			,Quad{2, 13, 14,  3}
			,Quad{3, 14,  7, 15}
			,Quad{3, 15,  8,  0}
			};

		std::for_each(begin(inner), end(inner), [output](Position pos)
			{fprintf(output, "v %.15g %.15g %.15g\n", pos.x(), pos.y(), 0.0);});

		std::for_each(begin(outer), end(outer), [output](Position pos)
			{fprintf(output, "v %.15g %.15g %.15g\n", pos.x(), pos.y(), 0.0);});

		std::for_each(begin(cross_points), end(cross_points), [output](Position pos)
			{fprintf(output, "v %.15g %.15g %.15g\n", pos.x(), pos.y(), 0.0);});

		std::for_each(begin(faces), end(faces), [output, k, k_0 = 8*blocks_inner.size()](Quad f)
			{
			fprintf(output, "f %zu %zu %zu %zu\n"
				, f.v_index[0] + 1 + 16*k + k_0
				, f.v_index[1] + 1 + 16*k + k_0
				, f.v_index[2] + 1 + 16*k + k_0
				, f.v_index[3] + 1 + 16*k + k_0);
			});
		}
	}
