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
	Cityplan::UiBox box{mainwin, Cityplan::UiBox::Orientation::Vertical};
	Cityplan::Simulation sim{Cityplan::Dimension{}.width(20).height(20)};
	Cityplan::SimulationControl sim_ctrl{sim, box, Cityplan::UiBox::Orientation::Horizontal};
	Cityplan::SimulationView sim_view
		{
		 sim
		,box.insertMode(Cityplan::UiBox::InsertMode{0, Cityplan::UiBox::FILL|Cityplan::UiBox::EXPAND})
		};
	mainwin.callback<0>(sim_ctrl);
	mainwin.show();
	gtk_main();
	}