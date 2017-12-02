#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/wave_ctrl.h"
#include "../source/manager/wave_manager.h"
#include "../include/ctrl_id.h"
#include "../include/msg_id.h"
#include "mini_wave_view.h"

void c_mini_wave_view::on_init_children(void)
{
	c_wave_ctrl *pWave = (c_wave_ctrl*)get_wnd_ptr(ID_MINI_WAV_VIEW_ECG_WAVE);
	c_wave_manage::get_instance()->register_wave_ctrl(WAVE_ECG2, pWave);
	pWave->set_wave_gain(GAIN_100);
	pWave->set_wave_speed(SPEED_X3);
	
	pWave = (c_wave_ctrl*)get_wnd_ptr(ID_MINI_WAV_VIEW_SPO2_WAVE);
	c_wave_manage::get_instance()->register_wave_ctrl(WAVE_SPO2, pWave);
	pWave->set_wave_gain(GAIN_100);
	pWave->set_wave_speed(SPEED_X3);

	pWave = (c_wave_ctrl*)get_wnd_ptr(ID_MINI_WAV_VIEW_RESP_WAVE);
	c_wave_manage::get_instance()->register_wave_ctrl(WAVE_RESP, pWave);
	pWave->set_wave_gain(GAIN_050);
	pWave->set_wave_speed(SPEED_X3);
}
