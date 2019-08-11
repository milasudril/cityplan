//@	{
//@  "targets":[{"name":"ui_window.o","type":"object","pkgconfig_libs":["gtk+-3.0"]}]
//@	}

#include "ui/ui_window.hpp"

#include <gtk/gtk.h>
#include <string>

using namespace Cityplan;

class UiWindow::Impl final:private UiWindow
	{
	public:
		Impl(const char* ti,UiContainer* owner);
		~Impl();

		const char* title() const noexcept
			{return m_title.c_str();}

		void title(const char* title_new)
			{
			gtk_window_set_title(m_handle,title_new);
			m_title=title_new;
			}

		void _add(GtkWidget* handle)
			{
			gtk_widget_set_margin_start(handle,4);
			gtk_widget_set_margin_end(handle,4);
			gtk_widget_set_margin_top(handle,4);
			gtk_widget_set_margin_bottom(handle,4);
			gtk_container_add(GTK_CONTAINER(m_handle),handle);
			}

		void _show()
			{gtk_widget_show_all(GTK_WIDGET(m_handle));}

		void _sensitive(bool val)
			{gtk_widget_set_sensitive(GTK_WIDGET(m_handle),val);}

		void* _toplevel() const
			{return m_handle;}

		void callback(Callback cb,void* cb_obj)
			{
			m_cb=cb;
			r_cb_obj=cb_obj;
			}

		void modal(bool state)
			{
			gtk_window_set_modal(m_handle,state);
			}

		void defaultSize(Dimension dim)
			{gtk_window_set_default_size(m_handle, dim.width(), dim.height());}


	private:
		static gboolean delete_callback(GtkWidget* widget,GdkEvent* event,void* user_data);

		Callback m_cb;
		void* r_cb_obj;
		GtkWindow* m_handle;
		GtkWidget* r_focus_old;
		std::string m_title;
		GdkPixbuf* m_icon;
	};

UiWindow::UiWindow(const char* title,UiContainer* owner)
	{m_impl=new Impl(title,owner);}

UiWindow::~UiWindow()
	{delete m_impl;}

const char* UiWindow::title() const noexcept
	{return m_impl->title();}

UiWindow& UiWindow::title(const char* title_new)
	{
	m_impl->title(title_new);
	return *this;
	}

UiWindow& UiWindow::add(void* handle)
	{
	m_impl->_add(GTK_WIDGET(handle));
	return *this;
	}

UiWindow& UiWindow::show()
	{
	m_impl->_show();
	return *this;
	}

UiWindow& UiWindow::sensitive(bool val)
	{
	m_impl->_sensitive(val);
	return *this;
	}

void* UiWindow::toplevel() const
	{return m_impl->_toplevel();}

UiWindow& UiWindow::callback(Callback cb, void* cb_obj)
	{
	m_impl->callback(cb, cb_obj);
	return *this;
	}

UiWindow& UiWindow::modal(bool state)
	{
	m_impl->modal(state);
	return *this;
	}

UiWindow::Impl::Impl(const char* ti,UiContainer* owner):UiWindow(*this)
	,r_cb_obj(nullptr),r_focus_old(nullptr)
	{
	auto widget=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(widget,"delete-event",G_CALLBACK(delete_callback),this);
	m_handle=GTK_WINDOW(widget);
	title(ti);
	if(owner!=nullptr)
		{gtk_window_set_transient_for(m_handle,GTK_WINDOW(owner->toplevel()));}
	m_icon=nullptr;
	}

UiWindow::Impl::~Impl()
	{
	m_impl=nullptr;
	r_cb_obj=nullptr;
	gtk_widget_destroy(GTK_WIDGET(m_handle));
	if(m_icon!=nullptr)
		{g_object_unref(m_icon);}
	}

gboolean UiWindow::Impl::delete_callback(GtkWidget* widget,GdkEvent* event,void* user_data)
	{
	auto self=reinterpret_cast<Impl*>(user_data);
	if(self->r_cb_obj!=nullptr)
		{self->m_cb(self->r_cb_obj, *self);}
	return TRUE;
	}

UiWindow& UiWindow::defaultSize(Dimension dim)
	{
	m_impl->defaultSize(dim);
	return *this;
	}

 void UiWindow::terminateApp()
	{gtk_main_quit();}
