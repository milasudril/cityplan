//@	{"targets":[{"name":"position.hpp","type":"include"}]}

#ifndef CITYPLAY_POSITION_HPP
#define CITYPLAY_POSITION_HPP

namespace Cityplan
	{
	class Position
		{
		public:
			using Scalar = double;

			Scalar x() const
				{return m_val[0];}

			Position& x(Scalar c)
				{
				m_val[0] = c;
				return *this;
				}

			Scalar y() const
				{return m_val[1];}

			Position& y(Scalar c)
				{
				m_val[1] = c;
				return *this;
				}

		private:
			using vec2 __attribute__((vector_size(16))) = double;
			vec2 m_val;
		};
	}

#endif
