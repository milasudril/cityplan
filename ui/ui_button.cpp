//@	{"targets":[{"name":"ui_button.o","type":"object","pkgconfig_libs":["gtk+-3.0"]}]}

#include "./ui_button.hpp"

#include <gtk/gtk.h>

using namespace Cityplan;

class UiButton::Impl:private UiButton
	{
	public:
		Impl(UiContainer& cnt,const char* label);
		~Impl();

		void callback(Callback cb, void* cb_obj)
			{
			r_cb=cb;
			r_cb_obj=cb_obj;
			}

		const char* label() const noexcept
			{return gtk_button_get_label(GTK_BUTTON(m_handle));}

		void label(const char* text) noexcept
			{return gtk_button_set_label(GTK_BUTTON(m_handle),text);}

		void state(bool s) noexcept
			{
			auto cb=r_cb;
			r_cb=nullptr;
			gtk_toggle_button_set_active(m_handle,s);
			r_cb=cb;
			}

		bool state() const noexcept
			{return gtk_toggle_button_get_active(m_handle);}

		void focus() noexcept
			{gtk_widget_grab_focus(GTK_WIDGET(m_handle));}

	private:
		Callback r_cb;
		void* r_cb_obj;
		GtkToggleButton* m_handle;

		static void clicked_callback(GtkWidget* widget, gpointer data);
		static gboolean focus_in_callback(GtkWidget* widget,GdkEvent* event,gpointer user_data);
	};

UiButton::UiButton(UiContainer& cnt,const char* label)
	{m_impl=new Impl(cnt,label);}

UiButton::~UiButton()
	{delete m_impl;}

UiButton& UiButton::callback(Callback cb, void* cb_obj)
	{
	m_impl->callback(cb, cb_obj);
	return *this;
	}

const char* UiButton::label() const noexcept
	{return m_impl->label();}

UiButton& UiButton::label(const char* text)
	{
	m_impl->label(text);
	return *this;
	}

UiButton& UiButton::state(bool s) noexcept
	{
	m_impl->state(s);
	return *this;
	}

UiButton& UiButton::focus() noexcept
	{
	m_impl->focus();
	return *this;
	}


bool UiButton::state() const noexcept
	{
	return m_impl->state();
	}



UiButton::Impl::Impl(UiContainer& cnt,const char* lab):UiButton(*this)
	,r_cb(nullptr)
	{
	auto widget=gtk_toggle_button_new();
	g_signal_connect(widget,"clicked", G_CALLBACK(clicked_callback),this);
	m_handle=GTK_TOGGLE_BUTTON(widget);
	g_object_ref_sink(widget);
	cnt.add(widget);
	label(lab);
	}

UiButton::Impl::~Impl()
	{
	m_impl=nullptr;
	r_cb=nullptr;
	gtk_widget_destroy(GTK_WIDGET(m_handle));
	g_object_unref(m_handle);
	}

void UiButton::Impl::clicked_callback(GtkWidget* widget, gpointer data)
	{
	auto state=reinterpret_cast<Impl*>(data);
	if(state->r_cb!=nullptr)
		{state->r_cb(state->r_cb_obj, *state);}
	}
