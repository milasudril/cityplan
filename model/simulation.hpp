//@	{
//@	 "targets":[{"name":"simulation.hpp","type":"include"}]
//@	}

#ifndef CITYPLAN_SIMULATION_HPP
#define CITYPLAN_SIMULATION_HPP

#include "city.hpp"

namespace Cityplan
	{
	class Simulation
		{
		public:
			explicit Simulation() : rng{"/dev/urandom"}{}

			void run()
				{
				while(makeNewBlock(m_city, [dim_min = m_dim_min](auto const& blocks_new)
					{
					return area(blocks_new.first) > area(Rectangle{dim_min});
					});
				}

			void reset()
				{city.clear();}

			City const& city() const
				{return city;}

			Simulation& city(City&& c)
				{
				m_city = std::move(c);
				return *this;
				}

			Dimension minDimension() const
				{return m_dim_min;}

			Simulation& minDimension(Dimension dim_min)
				{
				m_dim_min = dim_min;
				return *this;
				}

		private:
			std::random_device rng;
			Dimension m_dim_min;
			City m_city;
		};
	}

#endif
