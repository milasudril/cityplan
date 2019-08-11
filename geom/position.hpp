//@	{"targets":[{"name":"position.hpp","type":"include"}]}

#ifndef CITYPLAY_POSITION_HPP
#define CITYPLAY_POSITION_HPP

#include "./vec2.hpp"

#include <utility>

namespace Cityplan
	{
	class Position
		{
		public:
			using Scalar = decltype(std::declval<Vec2>()[0]);

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

			Position& operator+=(Vec2 offset)
				{
				m_val+=offset;
				return *this;
				}

			Position& operator-=(Vec2 offset)
				{
				m_val+=offset;
				return *this;
				}

		private:
			Vec2 m_val;
		};

	inline Position operator-(Position p, Vec2 offset)
		{
		p-=offset;
		return p;
		}

	inline Position operator+(Position p, Vec2 offset)
		{
		p+=offset;
		return p;
		}
	}

#endif
