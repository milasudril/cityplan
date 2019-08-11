//@	{
//@	 "targets":[{"name":"simulation.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"simulation.o","rel":"implementation"}]
//@	}

#ifndef CITYPLAN_SIMULATION_HPP
#define CITYPLAN_SIMULATION_HPP

#include "city.hpp"

namespace Cityplan
	{
	class Simulation
		{
		public:
			explicit Simulation();

			Simulation& run();

			City const& city() const
				{return m_city;}

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
			std::random_device m_rng;
			Dimension m_dim_min;
			City m_city;
		};
	}

#endif
