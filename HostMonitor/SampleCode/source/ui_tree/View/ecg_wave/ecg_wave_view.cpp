#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/wave_ctrl.h"

#include "../include/ctrl_id.h"
#include "../source/ui_ctrl_ex/ecg_wave_ctrl.h"
#include "../source/manager/wave_manager.h"
#include "../source/resource/font/strings.h"
#include "ecg_wave_view.h"

void c_ecg_wave_view::on_init_children(void)
{
	c_ecg_wave_ctrl *p_ecg_wave = (c_ecg_wave_ctrl*)get_wnd_ptr(ID_MAIN_SCREEN_ECG_WAVE_CTRL);
	if ( p_ecg_wave ==  NULL )
	{
		ASSERT(false);
		return;
	}

	p_ecg_wave->set_wave_speed(SPEED_X3);
	c_wave_manage::get_instance()->register_wave_ctrl(WAVE_ECG2, p_ecg_wave);
	p_ecg_wave->set_wave_gain(GAIN_100);
}
