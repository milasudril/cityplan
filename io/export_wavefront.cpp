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

	std::vector<std::array<Position, 4>> generateFaces(Rectangle const* begin, Rectangle const* end, double margin)
		{
		std::vector<std::array<Position, 4>> ret;
		std::transform(begin, end, std::back_inserter(ret),[margin](auto const& rect)
			{
			auto d_half = Vec2{0.5, 0.5}*(rect.dimension().offsetVector() - Vec2{margin, margin});
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
	}

void Cityplan::exportWavefront(Rectangle const* a, Rectangle const* b, FILE* output)
	{
	auto faces = generateFaces(a, b, 9.0);
	fprintf(output, "o BlockMask\n");
	std::for_each(begin(faces), end(faces), [output, k=0](auto const& plane) mutable
		{
		auto mesh = makeBox(plane, 100);
		std::for_each(std::begin(mesh.verts), std::end(mesh.verts), [output](Vertex const& v)
			{fprintf(output, "v %.15g %.15g %.15g\n", v.x, v.y, v.z);});

		std::for_each(std::begin(mesh.v_index), std::end(mesh.v_index), [output, k](auto const& f)
			{fprintf(output, "f %d %d %d %d\n", f.v_index[0] + 1 + 8*k, f.v_index[1] + 1 + 8*k, f.v_index[2] + 1 + 8*k, f.v_index[3] + 1 + 8*k);});
		++k;
		});
	}
