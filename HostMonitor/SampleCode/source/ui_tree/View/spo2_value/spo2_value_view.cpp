#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "gui_include/label.h"
#include "../source/ui_ctrl_ex/value_view.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "../source/resource/font/strings.h"
#include "gui_include/font.h"
#include "../include/ctrl_id.h"
#include "../source/manager/value_manager.h"
#include "../source/manager/value_ctrl_manager.h"
#include <string.h>
#include "spo2_value_view.h"

void c_spo2_value_view::on_init_children(void)
{
	//Register param ctrl.
	c_value_ctrl *p_value_spo2 = (c_value_ctrl*)get_wnd_ptr(ID_SPO2_VIEW_SPO2_VALUE);
	c_value_ctrl *p_value_pr = (c_value_ctrl*)get_wnd_ptr(ID_SPO2_VIEW_PR_VALUE);
	if (p_value_spo2 == NULL || p_value_pr == NULL)
	{
	    ASSERT(false);
		return;
	}

	c_value_ctrl_manage::get_instance()->config_param_ctrl_att(VALUE_SPO2, p_value_spo2);
	c_value_ctrl_manage::get_instance()->config_param_ctrl_att(VALUE_PR, p_value_pr);
	
	p_value_spo2->set_value_font_type(FONT_ENG_LLLB());
	p_value_pr->set_value_font_type(FONT_ENG_LLB());

	c_value_view::register_value_view(this);
}
