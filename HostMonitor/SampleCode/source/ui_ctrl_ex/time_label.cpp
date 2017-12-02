#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "gui_include/label.h"
#include "core_include/resource_type.h"
#include "core_include/word.h"
#include "core_include/surface.h"
#include "gui_include/font.h"
#include <string.h>
#include <stdio.h>
#include "time_label.h"

void c_time_label::on_init_children(void)
{
	m_font_type = FONT_ENG_SMB_AA();
	set_font_color(GLT_RGB(255,255,255));
	memset(&m_time, 0, sizeof(m_time));
}

void c_time_label::on_paint(void)
{
	T_TIME cur_time = get_time();
	char tmp_str[20];

	c_rect  rect;
	c_rect temp_rect;
	get_screen_rect(rect);

	if (cur_time.year != m_time.year
		|| cur_time.month != m_time.month
		|| cur_time.day != m_time.day)
	{
		temp_rect.m_left = rect.m_left;
		temp_rect.m_top = rect.m_top + 3;
		temp_rect.m_right = rect.m_left + 120;
		temp_rect.m_bottom = rect.m_top + 20;

		memset(tmp_str,0,sizeof(tmp_str));
		sprintf(tmp_str, "%04d-%02d-%02d", cur_time.year, cur_time.month, cur_time.day);
		fill_rect(temp_rect.m_left, temp_rect.m_top, temp_rect.m_right, temp_rect.m_bottom, m_bg_color);
		c_word::draw_string_in_rect(m_surface, m_z_order, tmp_str, temp_rect, m_font_type, m_font_color, m_bg_color, ALIGN_LEFT);
	}

	temp_rect.m_left = rect.m_left;// + 25;
	temp_rect.m_top = rect.m_top + 20;
	temp_rect.m_right = rect.m_left + 120;
	temp_rect.m_bottom = rect.m_top + 40;
	memset(tmp_str,0,sizeof(tmp_str));
	sprintf(tmp_str, "%02d:%02d:%02d", cur_time.hour, cur_time.minute, cur_time.second);
	fill_rect(temp_rect.m_left, temp_rect.m_top, temp_rect.m_right, temp_rect.m_bottom, m_bg_color);
	c_word::draw_string_in_rect(m_surface, m_z_order, tmp_str,temp_rect, m_font_type, m_font_color, m_bg_color, ALIGN_LEFT);
	m_time = cur_time;
}
