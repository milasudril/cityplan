//@	{"targets":[{"name":"ui_button.hpp","type":"include"}]}

#ifndef CITYPLAY_UICONTAINER_HPP
#define CITYPLAY_UICONTAINER_HPP

#include "./ui_container.hpp"

namespace Cityplan
	{
	class Button
		{
		public:
			explicit Button(Container& container,const char* label);
			~Button();

			Button& operator=(Button&& obj) noexcept
				{
				std::swap(obj.m_impl,m_impl);
				return *this;
				}

			Button(Button&& obj) noexcept:m_impl(obj.m_impl)
				{obj.m_impl=nullptr;}

			template<class Callback, class IdType, IdType id>
			Button& callback(Callback& cb)
				{
				auto cb_wrapper=[](void* rvc,Button& self)
					{
					auto x=reinterpret_cast<Callback*>(rvc);
					auto id=static_cast<IdType>(self.id());
					x->template clicked<id>(self);
					};
				return callback(cb_wrapper,&cb,static_cast<int>(id));
				}

			const char* label() const noexcept;

			Button& label(const char* text);

			int id() const noexcept;

			Button& state(bool s) noexcept;

			bool state() const noexcept;

			Button& focus() noexcept;

		private:
			class Impl;
			explicit Button(Impl& impl):m_impl(&impl){}
			Impl* m_impl;
			typedef void (*Callback)(void* cb_obj,Button& self);
			Button& callback(Callback cb,void* cb_obj,int id);
		};
	}

#endif
