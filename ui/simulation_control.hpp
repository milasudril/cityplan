//@	{"targets":[{"name":"simulation_control.hpp","type":"include"}]}

#ifndef CITYPLAY_SIMULATION_CONTROL_HPP
#define CITYPLAY_SIMULATION_CONTROL_HPP

#include "./ui_container.hpp"
#include "./ui_box.hpp"
#include "./ui_button.hpp"

#include "model/simulation.hpp"

namespace Cityplan
	{
	class SimulationControl
		{
		public:
			explicit SimulationControl(Simulation& sim, UiContainer& container, UiBox::Orientation orientation);

		private:
			UiBox m_box;
			UiButton m_load_state;
			UiButton m_discard;
			UiButton m_save;

			Simulation& r_sim;
		};

	}

#endif
