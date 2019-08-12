//@	{"targets":[{"name":"cityplan","type":"application", "autorun":0,"pkgconfig_libs":["gtk+-3.0"]}]}

#include "ui/ui_window.hpp"
#include "ui/ui_box.hpp"
#include "ui/simulation_control.hpp"
#include "ui/simulation_view.hpp"

#include <gtk/gtk.h>

int main(int argc, char* argv[])
	{
	gtk_init(&argc, &argv);


	Cityplan::UiWindow mainwin{"Cityplan"};
	mainwin.defaultSize(Cityplan::Dimension{}.width(800).height(500));
	Cityplan::UiBox box{mainwin, Cityplan::UiBox::Orientation::Vertical};

	Cityplan::Simulation sim{Cityplan::Dimension{}.width(20).height(20)};
	Cityplan::City c;
	c.append(Cityplan::Block{Cityplan::Position{}.x(0).y(0), Cityplan::Dimension{}.width(1300).height(1300)});
	sim.city(std::move(c));

	Cityplan::SimulationView sim_view
		{
		 sim
		,box.insertMode(Cityplan::UiBox::InsertMode{0, Cityplan::UiBox::FILL|Cityplan::UiBox::EXPAND|Cityplan::UiBox::POSITION_BACK})
		};
	Cityplan::SimulationControl sim_ctrl{sim, sim_view, box.insertMode(Cityplan::UiBox::InsertMode{0, 0}), Cityplan::UiBox::Orientation::Horizontal};
	mainwin.callback<0>(sim_ctrl);
	mainwin.show();
	gtk_main();
	}