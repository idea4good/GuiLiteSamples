#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../widgets_include/label.h"

#include "../include/ctrl_id.h"

#include "../source/ui_ctrl_ex/value_view.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "../source/ui_ctrl_ex/value_sub_ctrl.h"
#include "../source/manager/value_manager.h"
#include "../source/manager/value_ctrl_manager.h"
#include "mini_value_view.h"
#include <string.h>

void c_mini_value_view::on_init_children(void)
{
	c_value_sub_ctrl *pHr_value = (c_value_sub_ctrl*)get_wnd_ptr(ID_MINI_VALUE_VIEW_HR_VALUE);
	c_value_sub_ctrl *pSpo2_value = (c_value_sub_ctrl*)get_wnd_ptr(ID_MINI_VALUE_VIEW_SPO2_VALUE);
	c_value_sub_ctrl *pResp_value =(c_value_sub_ctrl*)get_wnd_ptr(ID_MINI_VALUE_VIEW_RESP_VALUE);
	if (pHr_value == 0 || pSpo2_value == 0 || pResp_value==0)
	{
		ASSERT(false);
		return;
	}

	c_value_ctrl_manage::get_instance()->config_param_ctrl_att(VALUE_HR, pHr_value);
	c_value_ctrl_manage::get_instance()->config_param_ctrl_att(VALUE_SPO2, pSpo2_value);
	c_value_ctrl_manage::get_instance()->config_param_ctrl_att(VALUE_RESP, pResp_value);
	
	pHr_value->set_value_font_type(c_theme::get_font(FONT_CUSTOM2));
	pSpo2_value->set_value_font_type(c_theme::get_font(FONT_CUSTOM2));
	pResp_value->set_value_font_type(c_theme::get_font(FONT_CUSTOM2));

	c_value_view::register_value_view(this);
}
