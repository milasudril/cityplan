//@	{
//@	 "targets":[{"name":"ui_box.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"ui_box.o","rel":"implementation"}]
//@	}

#ifndef CITYPLAN_UIBOX_HPP
#define CITYPLAN_UIBOX_HPP

#include "./ui_container.hpp"
#include "geom/rectangle.hpp"

namespace Cityplan
	{
	class UiBox : public UiContainer
		{
		public:
			static constexpr unsigned short FILL=1;
			static constexpr unsigned short EXPAND=2;
			struct InsertMode
				{
				unsigned short padding;
				unsigned short flags;
				};

			enum class Orientation : int{Vertical, Horizontal};

			explicit UiBox(UiContainer& parent, Orientation orientation, int global_spacing=2);
			~UiBox();

			UiBox& operator=(UiBox&& obj) noexcept
				{
				std::swap(obj.m_impl,m_impl);
				return *this;
				}

			UiBox(UiBox&& obj) noexcept:m_impl(obj.m_impl)
				{obj.m_impl=nullptr;}

			UiBox& add(void* handle);
			UiBox& show();
			UiBox& sensitive(bool val);
			void* toplevel() const;

			UiBox& homogenous(bool status) noexcept;
			UiBox& insertMode(const InsertMode& mode) noexcept;

			UiBox& alignment(float x) noexcept;

		protected:
			class Impl;
			explicit UiBox(UiBox::Impl& impl):m_impl(&impl){}
			Impl* m_impl;
		};
	}

#endif
