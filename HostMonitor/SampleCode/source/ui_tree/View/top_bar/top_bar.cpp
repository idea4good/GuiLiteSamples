#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../core_include/msg.h"
#include "../gui_include/label.h"
#include "../core_include/resource.h"
#include "../include/msg_id.h"
#include "../include/ctrl_id.h"
#include "top_bar.h"
#include "top_bar_xml.h"

GLT_BEGIN_MESSAGE_MAP(c_top_bar)
ON_GLT_USER_MSG(USR_MSG_UPDATE_TIME,c_top_bar::on_refurbish_time)
GLT_END_MESSAGE_MAP()

void c_top_bar::on_init_children(void)
{
	m_bg_color = GL_RGB(0,0,0);
	register_timer(1000, c_top_bar::sysinfo_timer_callback);
}

void c_top_bar::on_paint(void)
{
	c_rect rect;
	get_screen_rect(rect);
	fill_rect(rect.m_left, rect.m_top, rect.m_right, rect.m_bottom, m_bg_color);
	draw_hline(rect.m_left,rect.m_right,rect.m_bottom,GL_RGB(74,74,74));
}

void c_top_bar::on_refurbish_time(unsigned int wParam, unsigned int lParam)
{
   if (!m_is_visible_now) {
	   return;
   }

	c_wnd *p_ctl = get_wnd_ptr(ID_TOP_BAR_TIME_ID);
    if(p_ctl == NULL)
    {
       ASSERT(false);
	   return;
    }
    p_ctl->on_paint();
}

void c_top_bar::sysinfo_timer_callback(void* ptmr, void* parg)
{
	MSG_INFO msg_info;
	msg_info.dwMsgId = USR_MSG_UPDATE_TIME;
	write_usr_msg(&msg_info);
}
