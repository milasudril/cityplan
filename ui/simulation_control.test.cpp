//@	{"targets":[{"name":"simulation_control.test","type":"application", "autorun":1,"pkgconfig_libs":["gtk+-3.0"]}]}

#include "./simulation_control.hpp"

#include <gtk/gtk.h>

namespace
	{
	class UiContainerStub : public Cityplan::UiContainer
		{
		public:
			UiContainer& add(void*) override {return *this;}
			virtual UiContainer& show() override {return *this;}
			virtual UiContainer& sensitive(bool) {return *this;}
			virtual void* toplevel() const {return nullptr;}
		};
	}

namespace Test
	{
	void cityplanCreateSimulationControl()
		{
		Cityplan::Simulation sim{Cityplan::Dimension{}.width(1).height(1)};
		UiContainerStub container;
		Cityplan::SimulationControl simCtrl{sim, container, Cityplan::UiBox::Orientation::Horizontal};
		}
	}

int main(int argc, char* argv[])
	{
	gtk_init(&argc, &argv);
	Test::cityplanCreateSimulationControl();
	}
