//@	{"targets":[{"name":"simulation_control.hpp","type":"include"}]}

#ifndef CITYPLAY_SIMULATION_CONTROL_HPP
#define CITYPLAY_SIMULATION_CONTROL_HPP

#include "./ui_container.hpp"
#include "./ui_box.hpp"
#include "./ui_button.hpp"
#include "./ui_window.hpp"
#include "./simulation_view.hpp"

#include "model/simulation.hpp"

namespace Cityplan
	{
	class SimulationControl
		{
		public:
			explicit SimulationControl(Simulation& sim, SimulationView& view, UiContainer& container, UiBox::Orientation orientation):
				 r_sim{sim}
				,r_view{view}
				,m_city_initial{sim.city()}
				,m_box{container, orientation}
				,m_load_state
					{
					 m_box
						.homogenous(true)
						.insertMode(UiBox::InsertMode{0, UiBox::FILL|UiBox::EXPAND})
					,"Load state"
					}
				,m_gen_new{m_box, "Discard & generate new"}
				,m_qsave_new{m_box, "Save & generate new"}
				{
				m_city_initial = r_sim.city();
				m_load_state.callback<0>(*this);
				m_gen_new.callback<1>(*this);
				m_qsave_new.callback<2>(*this);
				}

			template<int id>
			void clicked(UiButton& btn)
				{
				btn.state(false);
				if constexpr(id == 1)
					{
					r_sim.city(City{m_city_initial}).run();
					}

				r_view.update();
				}

			template<int id>
			void closing(UiWindow&)
				{
				UiWindow::terminateApp();
				}

		private:
			Simulation& r_sim;
			SimulationView& r_view;

			City m_city_initial;

			UiBox m_box;
			UiButton m_load_state;
			UiButton m_gen_new;
			UiButton m_qsave_new;
		};

	}

#endif
