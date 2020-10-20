#include "../include/GuiLite.h"
#include "../include/ctrl_id.h"
#include "top_bar.h"
#include "top_bar_xml.h"

void c_top_bar::on_init_children(void)
{
	m_bg_color = GL_RGB(0,0,0);
	register_timer(1000, c_top_bar::sysinfo_timer_callback, this);
}

void c_top_bar::on_paint(void)
{
	c_rect rect;
	get_screen_rect(rect);
	m_surface->fill_rect(rect.m_left, rect.m_top, rect.m_right, rect.m_bottom, m_bg_color, m_z_order);
	m_surface->draw_hline(rect.m_left,rect.m_right,rect.m_bottom,GL_RGB(74,74,74), m_z_order);
}

void c_top_bar::sysinfo_timer_callback(void* param)//tbd
{
	c_top_bar* top_bar = (c_top_bar*)param;
	top_bar->get_wnd_ptr(ID_TOP_BAR_TIME_ID)->on_paint();
}
