#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../widgets_include/wave_ctrl.h"
#include "../source/ui_ctrl_ex/wave_ctrl_ex.h"
#include "../include/ctrl_id.h"
#include "../source/manager/wave_manager.h"
#include "resp_wave_view.h"

void c_resp_wave_view::on_init_children(void)
{
	c_bitmap_wave_ctrl *p_resp_wav = ((c_bitmap_wave_ctrl*)get_wnd_ptr(ID_MAIN_SCREEN_RESP_WAVE_CTRL));
	if(p_resp_wav == 0)
	{
		ASSERT(false);
		return;
	}
	p_resp_wav->set_bitmap(BITMAP_CUSTOM2);
	p_resp_wav->set_wave_speed(SPEED_X3);
	c_wave_manage::get_instance()->register_wave_ctrl(WAVE_RESP, p_resp_wav);
}
