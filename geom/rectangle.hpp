//@	{
//@	 "targets":[{"name":"rectangle.hpp","type":"include"}]
//@ ,"dependencies_extra":[{"ref":"rectangle.o","rel":"implementation"}]
//@	}

#ifndef CITYPLAY_RECTANGLE_HPP
#define CITYPLAY_RECTANGLE_HPP

#include "./position.hpp"
#include "./dimension.hpp"

#include <utility>

namespace Cityplan
	{
	class Rectangle
		{
		public:
			using Length = Dimension::Scalar;
			using Coordinate = Position::Scalar;

			explicit Rectangle(Position origin, Dimension dim):m_origin{origin}, m_dim{dim}{}

			Position position() const
				{return m_origin;}

			Rectangle& position(Position origin)
				{
				m_origin = origin;
				return *this;
				}

			Dimension dimension() const
				{return m_dim;}

			Rectangle& dimension(Dimension dim)
				{
				m_dim = dim;
				return *this;
				}

		private:
			Position m_origin;
			Dimension m_dim;
		};

	enum class SplitDirection:int{Vertical, Horizontal};

	inline auto width(Rectangle const& r)
		{return r.dimension().width();}

	inline auto height(Rectangle const& r)
		{return r.dimension().height();}

	inline auto area(Rectangle const& r)
		{return width(r) * height(r);}

	std::pair<Rectangle, Rectangle> split(Rectangle const& r, SplitDirection dir);
	}

#endif
