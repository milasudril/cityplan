//@	{
//@	 "targets":[{"name":"simulation.o","type":"object"}]
//@	}

#include "simulation.hpp"

namespace Cityplan
	{
	Simulation::Simulation(Dimension dim_min) : m_rng{"/dev/urandom"}, m_dim_min{dim_min}{}

	Simulation& Simulation::run()
		{
		if(m_city.blockCount() == 0)
			{return *this;}

		while(makeNewBlock(m_city, m_rng, [dim_min = m_dim_min](auto const& blocks_new)
			{
			return area(blocks_new.first) > area(Rectangle{dim_min});
			}));
		return *this;
		}
	}