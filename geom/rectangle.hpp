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

			Coordinate x0() const
				{return m_origin.x();}

			Rectangle& x0(Coordinate c)
				{
				m_origin.x(c);
				return *this;
				}

			Coordinate y0() const
				{return m_origin.y();}

			Rectangle& y0(Coordinate c)
				{
				m_origin.y(c);
				return *this;
				}

			Position position() const
				{return m_origin;}

			Rectangle& position(Position origin)
				{
				m_origin = origin;
				return *this;
				}



			Length width() const
				{return m_dim.width();}

			Rectangle& width(Length l)
				{
				m_dim.width(l);
				return *this;
				}

			Length height() const
				{return m_dim.height();}

			Rectangle& height(Length l)
				{
				m_dim.height(l);
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

	std::pair<Rectangle, Rectangle> split(Rectangle const& r, SplitDirection dir);
	}

#endif
