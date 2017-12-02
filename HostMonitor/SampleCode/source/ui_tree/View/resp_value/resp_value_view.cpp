#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "../source/ui_ctrl_ex/value_view.h"
#include "../include/ctrl_id.h"
#include "gui_include/font.h"
#include "../source/manager/value_manager.h"
#include "../source/manager/value_ctrl_manager.h"
#include <string.h>
#include "resp_value_view.h"

void c_resp_value_view::on_init_children(void)
{
	c_value_ctrl *p_rr = (c_value_ctrl*)get_wnd_ptr(ID_RESP_VIEW_RR_VALUE);
	if (p_rr == NULL)
	{
		ASSERT(false);
		return;
	}
	c_value_ctrl_manage::get_instance()->config_param_ctrl_att(VALUE_RESP, p_rr);

	p_rr->set_value_font_type(FONT_ENG_LLLB());

	c_value_view::register_value_view(this);
}
