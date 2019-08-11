//@	{"targets":[{"name":"ui_container.hpp","type":"include"}]}

#ifndef CITYPLAY_UICONTAINER_HPP
#define CITYPLAY_UICONTAINER_HPP

namespace Cityplan
	{
	class UiContainer
		{
		public:
			virtual ~UiContainer() = default;
			virtual UiContainer& add(void* handle) = 0;
			virtual UiContainer& show() = 0;
			virtual UiContainer& sensitive(bool val) = 0;
			virtual void* toplevel() const = 0;
		};

	}

#endif
