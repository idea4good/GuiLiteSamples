#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "gui_include/font.h"
#include "gui_include/label.h"
#include "core_include/resource_type.h"
#include "core_include/word.h"
#include "../source/ui_ctrl_ex/value_view.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "../include/ctrl_id.h"
#include "../source/resource/font/strings.h"
#include "gui_include/font.h"
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
    c_word::draw_string_in_rect(m_surface, m_z_order, "GuiLite Sample", t_rect, FONT_ENG_MB_AA(), GLT_RGB(255, 255, 255), GLT_RGB(0, 0, 0), ALIGN_LEFT | ALIGN_VCENTER);

	t_rect.m_left = rect.m_left + 250;
	c_word::draw_string_in_rect(m_surface, m_z_order, c_word::get_string(STR_ADULT), t_rect, FONT_ENG_MB_AA(), GLT_RGB(255, 255, 255), GLT_RGB(0, 0, 0), ALIGN_HCENTER | ALIGN_VCENTER);
}
