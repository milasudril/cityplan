//@	{
//@	 "targets":[{"name":"simulation_view.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"simulation_view.o","rel":"implementation"}]
//@	}

#ifndef CITYPLAY_SIMULATIONVIEW_HPP
#define CITYPLAY_SIMULATIONVIEW_HPP

#include "./ui_container.hpp"
#include "model/simulation.hpp"

#include <utility>

namespace Cityplan
	{
	class SimulationView
		{
		public:
			explicit SimulationView(Simulation& sim, UiContainer& container);
			~SimulationView();

			SimulationView& operator=(SimulationView&& obj) noexcept
				{
				std::swap(obj.m_impl, m_impl);
				return *this;
				}

			SimulationView(SimulationView&& obj) noexcept:m_impl(obj.m_impl)
				{obj.m_impl=nullptr;}

			SimulationView& update();

		private:
			class Impl;
			explicit SimulationView(Impl& impl):m_impl(&impl){}
			Impl* m_impl;
		};
	}

#endif
