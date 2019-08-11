//@	{
//@	 "targets":[{"name":"simulation.test","type":"application", "autorun":1}]
//@	}

#include "simulation.hpp"

#include <cassert>
#include <algorithm>

namespace Test
	{
	void cityplanSimulationRunOnEmpty()
		{
		Cityplan::Simulation sim{Cityplan::Dimension{}.width(20).height(20)};
		assert(sim.city().blockCount() == 0);
		sim.run();
		assert(sim.city().blockCount() == 0);
		}

	void cityplanSimulationRun()
		{
		Cityplan::Simulation sim{Cityplan::Dimension{}.width(0.25).height(0.25)};
		sim.city(Cityplan::City{}.append(Cityplan::Block
			{
			 Cityplan::Position{}.x(0).y(0)
			,Cityplan::Dimension{}.width(1).height(1)
			}));
		assert(sim.city().blockCount() == 1);
		sim.run();
		assert(sim.city().blockCount() > 1);
		auto& city = sim.city();
		assert(std::all_of(std::begin(city), std::end(city)
			, [min_dim = area(Cityplan::Rectangle{sim.minDimension()})](auto const& block)
			{
			printf("%.15g\n", area(block));
			return area(block) > min_dim;
			}));
		}
	}

int main()
	{
	Test::cityplanSimulationRunOnEmpty();
	Test::cityplanSimulationRun();

	}