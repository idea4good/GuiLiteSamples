#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"

#include "../gui_include/label.h"
#include "../core_include/resource.h"
#include "../core_include/word.h"
#include "../source/ui_ctrl_ex/value_view.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "../include/ctrl_id.h"
#include <stdio.h>
#include <string.h>
#include "patient_view.h"

void c_patient_view::on_paint(void)
{
	c_rect rect;
	c_rect t_rect;
	
	get_screen_rect(rect);
	t_rect = rect;
	t_rect.m_left = rect.m_left + 55;

	fill_rect(rect.m_left, rect.m_top, rect.m_right, rect.m_bottom,m_bg_color);
    c_word::draw_string_in_rect(m_surface, m_z_order, "GuiLite Sample", t_rect, c_my_resource::get_font(FONT_ENG_MB), GL_RGB(255, 255, 255), GL_RGB(0, 0, 0), ALIGN_LEFT | ALIGN_VCENTER);

	t_rect.m_left = rect.m_left + 250;
	c_word::draw_string_in_rect(m_surface, m_z_order, "ADU", t_rect, c_my_resource::get_font(FONT_ENG_MB), GL_RGB(255, 255, 255), GL_RGB(0, 0, 0), ALIGN_HCENTER | ALIGN_VCENTER);
}
