#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../widgets_include/label.h"

#include "../include/ctrl_id.h"
#include "../include/msg_id.h"

#include "../source/ui_ctrl_ex/value_view.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "../source/manager/value_manager.h"
#include "../source/manager/value_ctrl_manager.h"
#include "ecg_value_view.h"

void c_ecg_value_view::on_init_children(void)
{
	c_value_ctrl *p_hr_value = (c_value_ctrl*)get_wnd_ptr(ID_ECG_VIEW_HR_VALUE);
	c_value_ctrl *p_pvsc_value = (c_value_ctrl*)get_wnd_ptr(ID_ECG_VIEW_PVCs_VALUE);
	c_value_ctrl *p_st_ii_value =(c_value_ctrl*)get_wnd_ptr(ID_ECG_VIEW_STII_VALUE);
	if (p_hr_value == 0 || p_pvsc_value == 0 || p_st_ii_value==0)
	{
		ASSERT(false);
		return;
	}
	c_value_ctrl_manage::get_instance()->config_param_ctrl_att(VALUE_HR,	p_hr_value);
	c_value_ctrl_manage::get_instance()->config_param_ctrl_att(VALUE_PVCs,	p_pvsc_value);
	c_value_ctrl_manage::get_instance()->config_param_ctrl_att(VALUE_ST_II,p_st_ii_value);

	p_st_ii_value->set_name("ST_II");

    c_value_view::register_value_view(this);
}
