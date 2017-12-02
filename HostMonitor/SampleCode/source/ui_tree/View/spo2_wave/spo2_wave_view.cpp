#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/wave_ctrl.h"
#include "../source/manager/wave_manager.h"
#include "../include/ctrl_id.h"
#include "spo2_wave_view.h"

void c_spo2_wave_view::on_init_children(void)
{
	c_wave_ctrl *p_spo2_wav = (c_wave_ctrl*)get_wnd_ptr(ID_MAIN_SCREEN_SPO2_WAVE_CTRL);
	if (p_spo2_wav == NULL)
	{
		ASSERT(false);
		return;
	}
	p_spo2_wav->set_wave_speed(SPEED_X3);
	c_wave_manage::get_instance()->register_wave_ctrl(WAVE_SPO2, p_spo2_wav);
}
