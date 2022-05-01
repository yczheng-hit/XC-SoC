#ifndef VGASIM_H
#define VGASIM_H

#include <gtkmm.h>
#include "image.h"
#include "videomode.h"

class VGASIM : public Gtk::DrawingArea
{
public:
	typedef Cairo::RefPtr<Cairo::Context> CAIROGC;
	typedef const Cairo::RefPtr<Cairo::Context> CONTEXT;
	typedef Cairo::RefPtr<Cairo::ImageSurface> CAIROIMG;

	CAIROIMG m_pix;
	CAIROGC m_gc;
	IMAGE<unsigned> *m_data;
	VIDEOMODE m_mode;
	int m_vsync_count, m_hsync_count;
	bool m_out_of_sync;

	int m_last_vsync, m_last_hsync, m_last_r, m_last_g, m_last_b,
		m_pixel_clock_count;

	void initialize(void)
	{
		m_data = new IMAGE<unsigned>(m_mode.height(), m_mode.width());
		m_data->zeroize();

		m_vsync_count = 0;
		m_hsync_count = 0;
		m_out_of_sync = true;

		m_last_hsync = 1;
		m_last_vsync = 1;

		set_has_window(true);
		Widget::set_can_focus(false);
		set_size_request(m_mode.width(), m_mode.height());
	}

public:
	static const int CLOCKS_PER_PIXEL,
		BITS_PER_COLOR;

	VGASIM(void) : Gtk::DrawingArea(), m_mode(640, 480)
	{
		initialize();
	}

	VGASIM(const int w, const int h) : Gtk::DrawingArea(), m_mode(w, h)
	{
		initialize();
	}

	VGASIM(const char *h, const char *v) : Gtk::DrawingArea(), m_mode(h, v)
	{
		initialize();
	}

	void get_preferred_width_vfunc(int &min, int &nw) const;
	void get_preferred_height_vfunc(int &min, int &nw) const;
	void get_preferred_height_for_width_vfunc(int w, int &min, int &nw) const;
	void get_preferred_width_for_height_vfunc(int w, int &min, int &nw) const;

	virtual void on_realize();

	void operator()(const int vsync, const int hsync,
					const int r, const int g, const int b);
	virtual bool on_draw(CONTEXT &gc);
	bool syncd(void) { return !m_out_of_sync; }

	int width(void)
	{
		return m_mode.width();
	}

	int height(void)
	{
		return m_mode.height();
	}

	int raw_width(void)
	{
		return m_mode.raw_width();
	}

	int raw_height(void)
	{
		return m_mode.raw_height();
	}

	int hsync(void)
	{
		return m_mode.hsync();
	}

	int vsync(void)
	{
		return m_mode.vsync();
	}

	int hporch(void)
	{
		return m_mode.hporch();
	}

	int vporch(void)
	{
		return m_mode.vporch();
	}
};

class VGAWIN : public Gtk::Window
{
private:
	VGASIM *m_vgasim;

	void init(void);

public:
	VGAWIN(void);
	VGAWIN(const int w, const int h);
	VGAWIN(const char *h, const char *v);
	~VGAWIN(void) { delete m_vgasim; }
	void operator()(const int vsync, const int hsync, const int r, const int g, const int b)
	{
		(*m_vgasim)(vsync, hsync, r, g, b);
	}
	bool syncd(void) { return m_vgasim->syncd(); }

	int width(void)
	{
		return m_vgasim->width();
	}

	int height(void)
	{
		return m_vgasim->height();
	}

	int raw_width(void)
	{
		return m_vgasim->raw_width();
	}

	int raw_height(void)
	{
		return m_vgasim->raw_height();
	}

	int hsync(void)
	{
		return m_vgasim->hsync();
	}

	int vsync(void)
	{
		return m_vgasim->vsync();
	}

	int hporch(void)
	{
		return m_vgasim->hporch();
	}

	int vporch(void)
	{
		return m_vgasim->vporch();
	}
};

#endif
