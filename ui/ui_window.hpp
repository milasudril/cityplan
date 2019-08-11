//@	{
//@	 "targets":[{"name":"ui_window.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"ui_window.o","rel":"implementation"}]
//@	}

#ifndef CITYPLAN_UIWINDOW_HPP
#define CITYPLAN_UIWINDOW_HPP

#include "./ui_container.hpp"

#include <utility>

namespace Cityplan
	{
	class UiWindow:public UiContainer
		{
		public:
			explicit UiWindow(const char* title, UiContainer* owner=nullptr);
			~UiWindow() override;

			UiWindow& operator=(UiWindow&& obj) noexcept
				{
				std::swap(obj.m_impl,m_impl);
				return *this;
				}

			UiWindow(UiWindow&& obj) noexcept:m_impl(obj.m_impl)
				{obj.m_impl=nullptr;}

			UiWindow& add(void* handle) override;
			UiWindow& show() override;
			UiWindow& sensitive(bool val) override;
			void* toplevel() const override;

			const char* title() const noexcept;
			UiWindow& title(const char* title_new);

			template<auto id, class UiWindowCallback>
			UiWindow& callback(UiWindowCallback& cb) noexcept
				{
				auto cb_wrapper=[](void* rvc, UiWindow& self)
					{
					auto x=reinterpret_cast<Callback*>(rvc);
					x->template closing<id>(self);
					};
				return callback(cb_wrapper, &cb);
				}

			UiWindow& modal(bool state);

		protected:

			typedef void (*Callback)(void* cb_obj, UiWindow& self);
			UiWindow& callback(Callback cb, void* cb_obj);

			class Impl;
			Impl* m_impl;
			explicit UiWindow(Impl& impl):m_impl(&impl){}
		};
	}

#endif