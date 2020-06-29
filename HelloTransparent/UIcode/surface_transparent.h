class c_surface_transparent : public c_surface {
public:
	c_surface_transparent(unsigned int width, unsigned int height, unsigned int color_bytes, Z_ORDER_LEVEL max_zorder) : c_surface(width, height, 4)
	{
		m_max_zorder = max_zorder;
		m_display_color_bytes = color_bytes;
		
		c_rect layer_rect(0, 0, width, height);
		for (int i = Z_ORDER_LEVEL_0; i <= m_max_zorder; i++)
		{
			ASSERT(m_layers[i].fb = calloc(layer_rect.width() * layer_rect.height(), m_color_bytes));
			m_layers[i].rect = layer_rect;
		}
	}

	void clear_layer(unsigned int z_order)
	{
		memset(m_layers[z_order].fb, 0, m_layers[z_order].rect.width() * m_layers[z_order].rect.height() * m_color_bytes);
	}

	virtual void draw_pixel(int x, int y, unsigned int rgb, unsigned int z_order)
	{
		if (x >= m_width || y >= m_height || x < 0 || y < 0)
		{
			return;
		}
		if (z_order > (unsigned int)m_max_zorder)
		{
			ASSERT(false);
			return;
		}
		if (z_order > (unsigned int)m_top_zorder)
		{
			m_top_zorder = (Z_ORDER_LEVEL)z_order;
		}

		((unsigned int*)(m_layers[z_order].fb))[x + y * m_width] = rgb;
		*m_phy_write_index = *m_phy_write_index + 1;

		unsigned int a = GL_ARGB_A(rgb);
		unsigned int r = GL_RGB_R(rgb);
		unsigned int g = GL_RGB_G(rgb);
		unsigned int b = GL_RGB_B(rgb);
		if (z_order + 1 <= m_top_zorder)
		{//meet up layer
			unsigned int rgb_ = get_pixel(x, y, (z_order + 1));
			unsigned int a_ = GL_ARGB_A(rgb_);
			unsigned int r_ = GL_RGB_R(rgb_);
			unsigned int g_ = GL_RGB_G(rgb_);
			unsigned int b_ = GL_RGB_B(rgb_);

			unsigned int alpha_r = (r_ * a_ + r * (255 - a_)) / 255;
			unsigned int alpha_g = (g_ * a_ + g * (255 - a_)) / 255;
			unsigned int alpha_b = (b_ * a_ + b * (255 - a_)) / 255;
			rgb = GL_RGB(alpha_r, alpha_g, alpha_b);
		}
		if (m_display_color_bytes == 4)
		{
			((unsigned int*)m_phy_fb)[y * (m_display->get_width()) + x] = rgb;
		}
		else
		{
			((unsigned short*)m_phy_fb)[y * (m_display->get_width()) + x] = GL_RGB_32_to_16(rgb);
		}
	}

	virtual void fill_rect(int x0, int y0, int x1, int y1, unsigned int rgb, unsigned int z_order)
	{
		ASSERT(z_order <= (unsigned int)m_max_zorder);
		if (z_order > (unsigned int)m_top_zorder)
		{
			m_top_zorder = (Z_ORDER_LEVEL)z_order;
		}

		x0 = (x0 < 0) ? 0 : x0;
		y0 = (y0 < 0) ? 0 : y0;
		x1 = (x1 > m_layers[z_order].rect.m_right) ? m_layers[z_order].rect.m_right : x1;
		y1 = (y1 > m_layers[z_order].rect.m_bottom) ? m_layers[z_order].rect.m_bottom : y1;

		unsigned int* mem_fb;
		for (int y = y0; y <= y1; y++)
		{
			mem_fb = &((unsigned int*)m_layers[z_order].fb)[y * m_width + x0];
			for (int x = x0; x <= x1; x++)
			{
				*mem_fb++ = rgb;
			}
		}

		unsigned int a = GL_ARGB_A(rgb);
		unsigned int r = GL_RGB_R(rgb);
		unsigned int g = GL_RGB_G(rgb);
		unsigned int b = GL_RGB_B(rgb);
		int display_width = m_display->get_width();
		int display_height = m_display->get_height();

		c_rect upper_rect, lower_rect;
		if (z_order + 1 <= m_top_zorder)
		{
			upper_rect = m_layers[z_order + 1].rect;
		}
		if (z_order >= Z_ORDER_LEVEL_1)
		{
			lower_rect = m_layers[z_order - 1].rect;
		}

		for (int y = y0; y <= y1; y++)
		{
			unsigned int* phy_fb_32 = &((unsigned int*)m_phy_fb)[y * display_width + x0];
			unsigned short* phy_fb_16 = &((unsigned short*)m_phy_fb)[y * display_width + x0];
			*m_phy_write_index = *m_phy_write_index + 1;
			for (int x = x0; x <= x1; x++)
			{
				if (m_is_active && (x < display_width) && (y < display_height))
				{
					if (upper_rect.pt_in_rect(x, y))
					{
						unsigned int rgb_ = get_pixel(x, y, (z_order + 1));
						unsigned int a_ = GL_ARGB_A(rgb_);
						unsigned int r_ = GL_RGB_R(rgb_);
						unsigned int g_ = GL_RGB_G(rgb_);
						unsigned int b_ = GL_RGB_B(rgb_);
						unsigned int alpha_r = (r_ * a_ + r * (255 - a_)) / 255;
						unsigned int alpha_g = (g_ * a_ + g * (255 - a_)) / 255;
						unsigned int alpha_b = (b_ * a_ + b * (255 - a_)) / 255;
						rgb = GL_RGB(alpha_r, alpha_g, alpha_b);
					}
					else if (lower_rect.pt_in_rect(x, y))
					{
						unsigned int rgb_ = get_pixel(x, y, (z_order - 1));
						unsigned int r_ = GL_RGB_R(rgb_);
						unsigned int g_ = GL_RGB_G(rgb_);
						unsigned int b_ = GL_RGB_B(rgb_);
						unsigned int alpha_r = (r * a + r_ * (255 - a)) / 255;
						unsigned int alpha_g = (g * a + g_ * (255 - a)) / 255;
						unsigned int alpha_b = (b * a + b_ * (255 - a)) / 255;
						rgb = GL_RGB(alpha_r, alpha_g, alpha_b);
					}
					if (m_display_color_bytes == 4)
					{
						*phy_fb_32++ = rgb;
					}
					else
					{
						*phy_fb_16++ = GL_RGB_32_to_16(rgb);
					}
				}
			}
		}
	}

	void fill_rect(c_rect rect, unsigned int rgb, unsigned int z_order)
	{
		fill_rect(rect.m_left, rect.m_top, rect.m_right, rect.m_bottom, rgb, z_order);
	}

	virtual void draw_pixel_on_fb(int x, int y, unsigned int rgb)
	{
		m_color_bytes = m_display_color_bytes;
		c_surface::draw_pixel_on_fb(x, y, rgb);
		m_color_bytes = 4;
	}
	int m_display_color_bytes;
};
