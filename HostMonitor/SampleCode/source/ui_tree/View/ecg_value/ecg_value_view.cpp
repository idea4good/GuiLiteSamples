#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "gui_include/label.h"
#include "gui_include/font.h"

#include "../include/ctrl_id.h"
#include "../include/msg_id.h"

#include "../source/ui_ctrl_ex/value_view.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "../source/resource/font/strings.h"
#include "../source/manager/value_manager.h"
#include "../source/manager/value_ctrl_manager.h"
#include "ecg_value_view.h"

void c_ecg_value_view::on_init_children(void)
{
	c_value_ctrl *p_hr_value = (c_value_ctrl*)get_wnd_ptr(ID_ECG_VIEW_HR_VALUE);
	c_value_ctrl *p_pvsc_value = (c_value_ctrl*)get_wnd_ptr(ID_ECG_VIEW_PVCs_VALUE);
	c_value_ctrl *p_st_ii_value =(c_value_ctrl*)get_wnd_ptr(ID_ECG_VIEW_STII_VALUE);
	if (p_hr_value == NULL || p_pvsc_value == NULL || p_st_ii_value==NULL)
	{
		ASSERT(false);
		return;
	}
	c_value_ctrl_manage::get_instance()->config_param_ctrl_att(VALUE_HR,	p_hr_value);
	c_value_ctrl_manage::get_instance()->config_param_ctrl_att(VALUE_PVCs,	p_pvsc_value);
	c_value_ctrl_manage::get_instance()->config_param_ctrl_att(VALUE_ST_II,p_st_ii_value);

	p_hr_value->set_value_font_type(FONT_ENG_LLLB());
	p_pvsc_value->set_value_font_type(FONT_ENG_LLB());
	p_st_ii_value->set_value_font_type(FONT_ENG_LLB());

	p_st_ii_value->set_name(STR_ST_ANALYSIS_SETUP_DLG_S_STII);

    c_value_view::register_value_view(this);
}
