#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../core_include/surface.h"
#include "../core_include/resource.h"
#include "../core_include/word.h"
#include "../source/manager/value_manager.h"
#include "value_ctrl.h"
#include <string.h>
#include <stdio.h>

c_value_ctrl::c_value_ctrl()
{
	m_name_str = m_unit_str = 0;
	m_high_limit = m_low_limit = 0;
	m_value_dot_position = m_limit_dot_position = 0;
	m_value = 0;
	m_value_align_type = ALIGN_LEFT | ALIGN_VCENTER;
	memset(m_value_in_str, 0, sizeof(m_value_in_str));
}

void c_value_ctrl::refresh_value(short value, unsigned short dot_position, bool flash_or_not, unsigned int flash_color)
{
	c_rect rect;
	get_screen_rect(rect);

	if (flash_or_not)
	{
		//Remove old value
		c_word::draw_string_in_rect(m_surface, m_z_order, m_value_in_str, m_value_rect, m_value_font_type, m_bg_color, GL_ARGB(0, 0, 0, 0), m_value_align_type);
		
		memset(m_value_in_str, 0, sizeof(m_value_in_str));
		c_word::value_2_string(value, dot_position, m_value_in_str, sizeof(m_value_in_str));
		if (flash_color)
		{
			c_word::draw_string_in_rect(m_surface, m_z_order, m_value_in_str, m_value_rect, m_value_font_type, m_bg_color, flash_color, m_value_align_type);
		}
		else
		{
			c_word::draw_string_in_rect(m_surface, m_z_order, m_value_in_str, m_value_rect, m_value_font_type, m_name_color, m_bg_color, m_value_align_type);
		}
		goto EXIT;
	}
	
	if ((m_value != value) || (m_value_dot_position != dot_position))
	{
		//Remove old value
		c_word::draw_string_in_rect(m_surface, m_z_order, m_value_in_str, m_value_rect, m_value_font_type, m_bg_color, GL_ARGB(0, 0, 0, 0), m_value_align_type);
		
		memset(m_value_in_str, 0, sizeof(m_value_in_str));
		c_word::value_2_string(value, dot_position, m_value_in_str, sizeof(m_value_in_str));
		c_word::draw_string_in_rect(m_surface, m_z_order, m_value_in_str, m_value_rect, m_value_font_type, m_name_color, m_bg_color, m_value_align_type);
	}
EXIT:
	m_value = value;
	m_value_dot_position = dot_position;
}

void c_value_ctrl::pre_create_wnd()
{
	m_attr = (WND_ATTRIBUTION)(ATTR_VISIBLE | ATTR_VALUE);
	m_bg_color = GL_RGB(0,0,0);
}

void c_value_ctrl::on_paint(void)
{
	c_rect rect;
	get_screen_rect(rect);
	m_surface->fill_rect(rect, m_bg_color, m_z_order);

	int width, height;
	width = rect.m_right - rect.m_left;
	height = rect.m_bottom - rect.m_top;
	
	//show name
	c_word::draw_string(m_surface, m_z_order, m_name_str, rect.m_left + 1, rect.m_top, m_name_font_type, m_name_color, m_bg_color);

	//show unit
	int unitY = rect.m_top + (m_name_font_type->height)+1;
	c_word::draw_string(m_surface, m_z_order, m_unit_str, rect.m_left + 1, unitY, m_unit_font_type, m_unit_color, m_bg_color);

	//show high limit
	char limit[16] = { 0 };
	m_limit_rect.m_left = rect.m_left + 1; 
	m_limit_rect.m_top =  rect.m_bottom - height*0.05 - 2.0 * (m_limit_font_type->height);
	m_limit_rect.m_right = rect.m_left + width*0.25;		
	m_limit_rect.m_bottom = m_limit_rect.m_top + (m_limit_font_type->height);
	c_word::draw_value_in_rect(m_surface, m_z_order, m_high_limit, m_limit_dot_position, m_limit_rect, m_limit_font_type, m_limit_color, m_bg_color, m_value_align_type);


	//show low limit
	m_limit_rect.m_left = rect.m_left + 1;
	m_limit_rect.m_top = rect.m_bottom - height*0.05 - (m_limit_font_type->height);
	m_limit_rect.m_right = rect.m_left + width*0.25;
	m_limit_rect.m_bottom = m_limit_rect.m_top + (m_limit_font_type->height);
	c_word::draw_value_in_rect(m_surface, m_z_order, m_low_limit, m_limit_dot_position, m_limit_rect, m_limit_font_type, m_limit_color, m_bg_color, m_value_align_type);

	//show value
	m_value_rect.m_left = rect.m_left + 50;
	m_value_rect.m_top = rect.m_top +(height - (m_value_font_type->height)) / 2;

	c_word::value_2_string(m_value, m_limit_dot_position, m_value_in_str, sizeof(m_value_in_str));
	int strWidth, strHeight;
	c_word::get_str_size(m_value_in_str, m_value_font_type, strWidth, strHeight);

	m_value_rect.m_right = m_value_rect.m_left + strWidth;
	m_value_rect.m_bottom = m_value_rect.m_top + (m_value_font_type->height);

	c_word::draw_string_in_rect(m_surface, m_z_order, m_value_in_str, m_value_rect, m_value_font_type, m_name_color, m_bg_color, m_value_align_type);
}
