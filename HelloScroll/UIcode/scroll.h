class c_surface_offset : public c_surface {
public:
	c_surface_offset(unsigned int width, unsigned int height, unsigned int color_bytes, int offset_x, int offset_y) :	c_surface(width, height, color_bytes), m_offset_x(offset_x), m_offset_y(offset_y) {}
	virtual void draw_pixel(int x, int y, unsigned int rgb, unsigned int z_order)
	{
		x -= m_offset_x;
		y -= m_offset_y;
		c_surface::draw_pixel(x, y, rgb, z_order);
	}
	virtual void fill_rect(int x0, int y0, int x1, int y1, unsigned int rgb, unsigned int z_order)
	{
		x0 -= m_offset_x;
		x1 -= m_offset_x;
		y0 -= m_offset_y;
		y1 -= m_offset_y;
		c_surface::fill_rect(x0, y0, x1, y1, rgb, z_order);
	}
	int m_offset_x;
	int m_offset_y;
};

#define MOVE_THRESHOLD	10
class c_scroll_view : c_wnd
{
	virtual void pre_create_wnd()
	{
		m_bg_color = GL_RGB(220, 220, 220);
	}
	virtual void on_init_children()
	{
		m_parent_surface = m_surface;
		int width, height;
		width = height = 0;
		c_wnd* tmp = m_top_child;
		c_rect rect;
		while (tmp)
		{
			tmp->get_wnd_rect(rect);
			if (width < rect.m_right)
			{
				width = rect.m_right + 1;
			}
			if (height < rect.m_bottom)
			{
				height = rect.m_bottom + 1;
			}
			tmp = tmp->get_next_sibling();
		}

		get_screen_rect(rect);
		if (width < rect.Width())
		{
			width = rect.Width();
		}
		if (height < rect.Height())
		{
			height = rect.Height();
		}
		
		m_mem_surface = new c_surface_offset(width, height, 2, rect.m_left, rect.m_top);
		m_mem_display = new c_display(calloc(width * height, 2), width, height, m_mem_surface);

		//change surface
		set_surface(m_mem_surface);
		tmp = m_top_child;
		while (tmp)
		{
			tmp->set_surface(m_mem_surface);
			tmp = tmp->get_next_sibling();
		}
	}
	virtual void on_paint()
	{
		m_mem_surface->fill_rect(m_mem_surface->m_offset_x, m_mem_surface->m_offset_y, m_mem_surface->m_offset_x + m_mem_surface->get_width() - 1, m_mem_surface->m_offset_y + m_mem_surface->get_height() - 1, m_bg_color, m_z_order);
	}
	virtual void show_window()
	{
		c_wnd::show_window();
		flush_mem_surface();
	}
	virtual void on_touch(int x, int y, TOUCH_ACTION action)
	{
		c_rect rect;
		get_wnd_rect(rect);
		bool force_update = false;

		//TOUCH_UP
		if (action == TOUCH_UP)
		{
			c_wnd::on_touch(x + m_offset_x, y + m_offset_y, TOUCH_DOWN);
			c_wnd::on_touch(x + m_offset_x, y + m_offset_y, TOUCH_UP);
			goto EXIT;
		}

		//TOUCH_DOWN
		if (m_touch_action == TOUCH_UP)
		{
			m_down_x = x;
			m_down_y = y;
		}
		else if (abs(m_down_y - y) > MOVE_THRESHOLD)
		{
			int offset_y = m_offset_y;
			offset_y += (m_down_y - y);
			if (offset_y > (m_mem_surface->get_height() - rect.Height()))
			{
				offset_y = (m_mem_surface->get_height() - rect.Height());
			}
			offset_y = (offset_y < 0) ? 0 : offset_y;
			if (offset_y != m_offset_y)
			{
				force_update = true;
				m_offset_y = offset_y;
			}
		}
		else if (abs(m_down_x - x) > MOVE_THRESHOLD)
		{
			int offset_x = m_offset_x;
			offset_x += (m_down_x - x);
			if (offset_x > (m_mem_surface->get_width() - rect.Width()))
			{
				offset_x = (m_mem_surface->get_width() - rect.Width());
			}
			offset_x = (offset_x < 0) ? 0 : offset_x;
			if (offset_x != m_offset_x)
			{
				force_update = true;
				m_offset_x = offset_x;
			}
		}
	EXIT:
		m_touch_action = action;
		flush_mem_surface(force_update);
	}
	void flush_mem_surface(bool force_update = false)
	{
		c_rect rect;
		get_screen_rect(rect);
		ASSERT(m_offset_y + rect.Height() <= m_mem_surface->get_height());
		ASSERT(m_offset_x + rect.Width() <= m_mem_surface->get_width());
		unsigned short* fb = (unsigned short*)m_mem_display->get_updated_fb(0, 0, force_update);
		if (!fb)
		{
			return;
		}

		for (int y = rect.m_top; y <= rect.m_bottom; y++)
		{
			unsigned short* rgb_16 = fb + m_mem_display->get_width() * (m_offset_y + y - rect.m_top) + m_offset_x;
			for (int x = rect.m_left; x <= rect.m_right; x++)
			{
				m_parent_surface->draw_pixel(x, y, GL_RGB_16_to_32(*rgb_16), m_z_order);
				rgb_16++;
			}
		}
	}
	void on_button_clicked(int ctrl_id, int param)
	{
		notify_parent(GL_BN_CLICKED, ctrl_id);
	}

	GL_DECLARE_MESSAGE_MAP()//delcare message
private:
	TOUCH_ACTION m_touch_action = TOUCH_UP;
	c_display* m_mem_display;
	c_surface_offset* m_mem_surface;
	c_surface* m_parent_surface;
	int m_offset_x = 0;
	int m_offset_y = 0;
	int m_down_x, m_down_y;
};

#ifdef GUILITE_ON
GL_BEGIN_MESSAGE_MAP(c_scroll_view)
ON_GL_BN_CLICKED(c_scroll_view::on_button_clicked)
GL_END_MESSAGE_MAP()
#endif
