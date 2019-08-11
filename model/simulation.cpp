//@	{
//@	 "targets":[{"name":"simulation.o","type":"object"}]
//@	}

#include "simulation.hpp"

namespace Cityplan
	{
	Simulation::Simulation() : m_rng{"/dev/urandom"}{}

	Simulation& Simulation::run()
		{
		while(makeNewBlock(m_city, m_rng, [dim_min = m_dim_min](auto const& blocks_new)
			{
			return area(blocks_new.first) > area(Rectangle{dim_min});
			}));
		return *this;
		}
	}