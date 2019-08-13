//@	{"targets":[{"name":"simulation_view.o","type":"object","pkgconfig_libs":["gtk+-3.0"]}]}

#include "./simulation_view.hpp"

#include <gtk/gtk.h>
#include <algorithm>

using namespace Cityplan;

class SimulationView::Impl:private SimulationView
	{
	public:
		Impl(Simulation& sim, UiContainer& cnt);
		~Impl();

		void update()
			{gtk_widget_queue_draw(GTK_WIDGET(m_handle));}

	private:
		Simulation& r_sim;
		GtkDrawingArea* m_handle;
		static gboolean render(GtkWidget* widget, cairo_t* cr, void* data);
	};

SimulationView::SimulationView(Simulation& sim, UiContainer& cnt)
	{m_impl=new Impl(sim, cnt);}

SimulationView::~SimulationView()
	{delete m_impl;}


SimulationView::Impl::Impl(Simulation& sim, UiContainer& cnt):SimulationView(*this), r_sim{sim}
	{
	auto widget=gtk_drawing_area_new();
	m_handle=GTK_DRAWING_AREA(widget);
	g_signal_connect(GTK_WIDGET(widget), "draw", G_CALLBACK(render), this);
	g_object_ref_sink(widget);
	cnt.add(widget);
	}

SimulationView::Impl::~Impl()
	{
	m_impl=nullptr;
	gtk_widget_destroy(GTK_WIDGET(m_handle));
	g_object_unref(m_handle);
	}

SimulationView& SimulationView::update()
	{
	m_impl->update();
	return *this;
	}

static void draw(Rectangle const& r, Dimension viewport, cairo_t* cr)
	{
	auto o = Vec2{0.5, 0.5}*viewport;
	// TODO: Compute scale factor
	auto scale = 0.75*std::min(viewport.width(), viewport.height())/1300;
	auto o_x = o.width();  // Compute midpoint
	auto o_y = o.height();

	auto dim_rect = Vec2{0.5, 0.5}*r.dimension();
	auto pos = r.position();

	cairo_rectangle(cr
		,o_x - (dim_rect.width() - pos.x())*scale
		,o_y - (dim_rect.height() + pos.y())*scale
		,r.dimension().width()*scale
		,r.dimension().height()*scale);
	}

gboolean SimulationView::Impl::render(GtkWidget* widget, cairo_t* cr, void* data)
	{
	GtkStyleContext* context = gtk_widget_get_style_context (widget);
	auto& self = *reinterpret_cast<SimulationView::Impl const*>(data);

	auto dim_out = Dimension{}.width(gtk_widget_get_allocated_width (widget))
		.height(gtk_widget_get_allocated_height(widget));

	gtk_render_background (context, cr, 0, 0, dim_out.width(), dim_out.height());

	GdkRGBA color;
	gtk_style_context_get_color (context,
								gtk_style_context_get_state (context),
								&color);
	gdk_cairo_set_source_rgba (cr, &color);
	cairo_set_line_width(cr, 0.5);
	auto& city = self.r_sim.city();
	std::for_each(std::begin(city), std::end(city), [cr, dim_out](auto const& r)
		{draw(r, dim_out, cr);});

	cairo_stroke(cr);
	return TRUE;
	}
