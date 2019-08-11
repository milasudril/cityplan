//@	{
//@	 "targets":[{"name":"ui_button.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"ui_button.o","rel":"implementation"}]
//@	}

#ifndef CITYPLAY_UIBUTTON_HPP
#define CITYPLAY_UIBUTTON_HPP

#include "./ui_container.hpp"

#include <utility>

namespace Cityplan
	{
	class UiButton
		{
		public:
			explicit UiButton(UiContainer& container, const char* label);
			~UiButton();

			UiButton& operator=(UiButton&& obj) noexcept
				{
				std::swap(obj.m_impl, m_impl);
				return *this;
				}

			UiButton(UiButton&& obj) noexcept:m_impl(obj.m_impl)
				{obj.m_impl=nullptr;}

			template<auto id, class Callback>
			UiButton& callback(Callback& cb)
				{
				auto cb_wrapper=[](void* rvc, UiButton& self)
					{
					auto x=reinterpret_cast<Callback*>(rvc);
					x->template clicked<id>(self);
					};
				return callback(cb_wrapper, &cb);
				}

			const char* label() const noexcept;

			UiButton& label(const char* text);

			UiButton& state(bool s) noexcept;

			bool state() const noexcept;

			UiButton& focus() noexcept;

		private:
			class Impl;
			explicit UiButton(Impl& impl):m_impl(&impl){}
			Impl* m_impl;
			typedef void (*Callback)(void* cb_obj,UiButton& self);
			UiButton& callback(Callback cb, void* cb_obj);
		};
	}

#endif
