#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/wave_ctrl.h"
#include "../source/manager/wave_manager.h"
#include "../include/ctrl_id.h"
#include "ecg_7wave_view.h"

void c_ecg_7wave_screen_view::on_init_children(void)
{
	c_wave_ctrl *p_ecg_wave = NULL;

	int index = 0;
	for (int id = ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE1; id <= ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE7; id++,index++)
	{
		p_ecg_wave = (c_wave_ctrl*)get_wnd_ptr(id);
		if (p_ecg_wave == NULL)
		{
			ASSERT(false);
			return;
		}
		p_ecg_wave->set_wave_speed(SPEED_X3);
		if(id == ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE1)
		{
			c_wave_manage::get_instance()->register_wave_ctrl(WAVE_ECG2, p_ecg_wave);
		}
		else if(id == ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE2)
		{
			c_wave_manage::get_instance()->register_wave_ctrl(WAVE_ECG1, p_ecg_wave);
		}
		else
		{
			c_wave_manage::get_instance()->register_wave_ctrl(WAVE_TYPE(WAVE_ECG1 + index), p_ecg_wave);
		}
		p_ecg_wave->set_wave_gain(GAIN_100);
	}
}
