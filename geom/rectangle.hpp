//@	{"targets":[{"name":"rectangle.hpp","type":"include"}]}

#ifndef CITYPLAY_RECTANGLE_HPP
#define CITYPLAY_RECTANGLE_HPP

namespace Cityplan
	{
	class Rectangle
		{
		public:
			using Length = Dimension::Scalar;
			ussing Coordinate = Position::Scalar;

			explicit Rectangle(Position origin, Dimension dim):m_origin{origin}, m_dim{dim}{}

			Coordinate x0() const
				{return m_origin.x();}

			Rectangle& x0(Coordinate c)
				{
				m_origin.x0(c);
				return *this;
				}

			Coordinate y0() const
				{return m_origin.y();}

			Rectangle& y0(Coordinate c)
				{
				m_origin.y0(c);
				return *this;
				}

			Position position() const
				{return m_origin;}

			Position& position(Position o)
				{
				m_origin = o;
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

			Rectangle& height(Length l) const
				{
				m_dim.height(l);
				return *this;
				}

			Dimension dimension() const
				{return m_dim;}

			Dimension& dimension(Dimension d)
				{
				m_dim = o;
				return *this;
				}



		private:
			Position m_origin;
			Dimension m_dim;
		};
	}

#endif
