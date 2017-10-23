#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../core_include/surface.h"
#include "../core_include/resource_type.h"
#include "../core_include/word.h"
#include "../gui_include/shape_resource.h"
#include "../source/manager/value_manager.h"
#include "value_ctrl.h"
#include <string.h>
#include <stdio.h>

c_value_ctrl::c_value_ctrl()
{
	m_name_id = m_unit_strid = 0;
	m_high_limit = m_low_limit = 0;
	m_value_dot_position = m_limit_dot_position = 0;
	m_value = XXX;
	m_value_align_type = ALIGN_LEFT | ALIGN_VCENTER;
	memset(m_value_in_str, 0, sizeof(m_value_in_str));
}

void c_value_ctrl::refurbish_value(short value, unsigned short dot_position, bool flash_or_not, unsigned int flash_color)
{
	if (!m_is_visible_now)
	{
		return;
	}
	c_rect rect;
	get_screen_rect(rect);

	c_word *p = c_word::get_instance();
	memset(m_value_in_str, 0, sizeof(m_value_in_str));
	value_2_string(value, m_value_in_str, dot_position);
	int strLen = p->get_str_pixel_length(m_value_in_str, m_value_font_type);

	m_value_rect.m_right = m_value_rect.m_left + strLen;
	if (m_value_rect.m_right > rect.m_right)
	{
		m_value_rect.m_right = rect.m_right - 2;
	}
	m_max_value_rect.m_right = ((m_value_rect.m_right > m_max_value_rect.m_right) ? m_value_rect.m_right : m_max_value_rect.m_right);

	if (flash_or_not)
	{
		fill_rect(m_max_value_rect.m_left, m_max_value_rect.m_top, m_max_value_rect.m_right, m_max_value_rect.m_bottom, m_bg_color);
		if (flash_color)
		{
			p->draw_string_in_rect(m_surface, m_z_order, m_value_in_str, m_value_rect, m_value_font_type, m_bg_color, flash_color, m_value_align_type);
		}
		else
		{
			p->draw_string_in_rect(m_surface, m_z_order, m_value_in_str, m_value_rect, m_value_font_type, m_name_color, m_bg_color, m_value_align_type);
		}
		goto EXIT;
	}
	
	if ((m_value != value) || (m_value_dot_position != dot_position))
	{
		fill_rect(m_max_value_rect.m_left, m_max_value_rect.m_top, m_max_value_rect.m_right, m_max_value_rect.m_bottom, m_bg_color);
		p->draw_string_in_rect(m_surface, m_z_order, m_value_in_str, m_value_rect, m_value_font_type, m_name_color, m_bg_color, m_value_align_type);
	}

EXIT:
	m_value = value;
	m_value_dot_position = dot_position;
	m_max_value_rect = m_value_rect;
}

void c_value_ctrl::pre_create_wnd()
{
	m_style = GLT_ATTR_VISIBLE;
	m_bg_color = GLT_RGB(0,0,0);
}

void c_value_ctrl::on_paint(void)
{
	c_rect rect;
	get_screen_rect(rect);
	fill_rect(rect.m_left,rect.m_top,rect.m_right,rect.m_bottom,m_bg_color);

	int width, height;
	width = rect.m_right - rect.m_left;
	height = rect.m_bottom - rect.m_top;

	c_word *p = c_word::get_instance();

	//show name
	p->draw_string(m_surface, m_z_order, m_name_id, rect.m_left + 1, rect.m_top, m_name_font_type, m_name_color, m_bg_color);

	//show unit
	int unitY = rect.m_top + p->get_font_ysize(m_name_font_type)+1;
	p->draw_string(m_surface, m_z_order, m_unit_strid, rect.m_left + 1, unitY, m_unit_font_type, m_unit_color, m_bg_color);

	//show high limit
	char limit[16] = { 0 };
	m_limit_rect.m_left = rect.m_left + 1; 
	m_limit_rect.m_top =  rect.m_bottom - height*0.05 - 2.0 * p->get_font_ysize(m_limit_font_type);
	m_limit_rect.m_right = rect.m_left + width*0.25;		
	m_limit_rect.m_bottom = m_limit_rect.m_top + p->get_font_ysize(m_limit_font_type);
	int temp_high_limit_bottom = m_limit_rect.m_bottom;
	if (m_high_limit != XXX)
	{
		value_2_string(m_high_limit, limit, m_limit_dot_position);
		p->draw_string_in_rect(m_surface, m_z_order, limit, m_limit_rect, m_limit_font_type, m_limit_color, m_bg_color, m_value_align_type);
	}

	//show low limit
	m_limit_rect.m_left = rect.m_left + 1;
	m_limit_rect.m_top = rect.m_bottom - height*0.05 - p->get_font_ysize(m_limit_font_type);
	m_limit_rect.m_right = rect.m_left + width*0.25;
	m_limit_rect.m_bottom = m_limit_rect.m_top +p->get_font_ysize(m_limit_font_type);
	if (m_low_limit != XXX)
	{
		value_2_string(m_low_limit, limit, m_limit_dot_position);
		p->draw_string_in_rect(m_surface, m_z_order, limit, m_limit_rect, m_limit_font_type, m_limit_color, m_bg_color, m_value_align_type);
	}

	//show value
	m_value_rect.m_left = rect.m_left + 50;
	m_value_rect.m_top = rect.m_top +(height-p->get_font_ysize(m_value_font_type)) / 2;

	value_2_string(m_value, m_value_in_str, m_limit_dot_position);
	int strLen = p->get_str_pixel_length(m_value_in_str, m_value_font_type);

	m_value_rect.m_right = m_value_rect.m_left + strLen;
	m_value_rect.m_bottom = m_value_rect.m_top + p->get_font_ysize(m_value_font_type);

	m_max_value_rect = m_value_rect;
	p->draw_string_in_rect(m_surface, m_z_order, m_value_in_str, m_value_rect, m_value_font_type, m_name_color, m_bg_color, m_value_align_type);
}
