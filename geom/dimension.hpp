//@	{"targets":[{"name":"dimension.hpp","type":"include"}]}

#ifndef CITYPLAY_DIMENSION_HPP
#define CITYPLAY_DIMENSION_HPP

#include "vec2.hpp"

#include <utility>

namespace Cityplan
	{
	class Dimension
		{
		public:
			using Scalar = decltype(std::declval<Vec2>()[0]);

			Scalar width() const
				{return m_val[0];}

			Dimension& width(Scalar c)
				{
				m_val[0] = c;
				return *this;
				}

			Scalar height() const
				{return m_val[1];}

			Dimension& height(Scalar c)
				{
				m_val[1] = c;
				return *this;
				}

		private:
			Vec2 m_val;
		};
	}

#endif
