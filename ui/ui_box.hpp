//@	{"targets":[{"name":"ui_box.hpp","type":"include"}]}

#ifndef CITYPLAY_UICONTAINER_HPP
#define CITYPLAY_UICONTAINER_HPP

namespace Cityplan
	{
	class UiBox final: public UiContainer
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

			explicit Box(Container& parent, Orientation orientation, int global_spacing=2);
			~Box();

			Box& operator=(Box&& obj) noexcept
				{
				std::swap(obj.m_impl,m_impl);
				return *this;
				}

			Box(Box&& obj) noexcept:m_impl(obj.m_impl)
				{obj.m_impl=nullptr;}

			Box& add(void* handle);
			Box& show();
			Box& sensitive(bool val);
			void* toplevel() const;

			Box& homogenous(bool status) noexcept;
			Box& insertMode(const InsertMode& mode) noexcept;

			Box& alignment(float x) noexcept;

			Rectangle boundingBox() const noexcept;

		private:
			class Impl;
			explicit Box(Box::Impl& impl):m_impl(&impl){}
			Impl* m_impl;
		};
	}

#endif
