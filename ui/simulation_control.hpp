//@	{"targets":[{"name":"simulation_control.hpp","type":"include"}]}

#ifndef CITYPLAY_SIMULATION_CONTROL_HPP
#define CITYPLAY_SIMULATION_CONTROL_HPP

#include "./ui_container.hpp"
#include "./ui_box.hpp"
#include "./ui_button.hpp"
#include "./ui_window.hpp"

#include "model/simulation.hpp"

namespace Cityplan
	{
	class SimulationControl
		{
		public:
			explicit SimulationControl(Simulation& sim, UiContainer& container, UiBox::Orientation orientation):
				 r_sim{sim}
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
				m_load_state.callback<0>(*this);
				m_gen_new.callback<1>(*this);
				m_qsave_new.callback<2>(*this);
				}

			template<int id>
			void clicked(UiButton& btn)
				{
				btn.state(false);
				printf("Hej %d\n", id);
				}

			template<int id>
			void closing(UiWindow&)
				{
				UiWindow::terminateApp();
				}

		private:
			Simulation& r_sim;

			UiBox m_box;
			UiButton m_load_state;
			UiButton m_gen_new;
			UiButton m_qsave_new;
		};

	}

#endif
