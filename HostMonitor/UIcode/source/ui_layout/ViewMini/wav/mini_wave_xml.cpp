#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../widgets_include/wave_ctrl.h"
#include "../source/ui_ctrl_ex/wave_ctrl_ex.h"
#include "../include/define.h"
#include "../include/ctrl_id.h"
#include "mini_wave_xml.h"

#define WAVE_WIDTH 		(MINI_UI_WIDTH * 2 / 3)
#define WAVE_HEIGHT 	(MINI_UI_HEIGHT / 3)

static c_ecg_wave_ctrl	s_ecg_wave;
static c_wave_ctrl		s_spo2_wave;
static c_wave_ctrl		s_resp_wave;

WND_TREE g_mini_wave_view_children[]=
{
	{(c_wnd*)&s_ecg_wave, ID_MINI_WAV_VIEW_ECG_WAVE,   0, 0, 0,					WAVE_WIDTH, WAVE_HEIGHT, 0 },
	{(c_wnd*)&s_spo2_wave, ID_MINI_WAV_VIEW_SPO2_WAVE, 0, 0, WAVE_HEIGHT,		WAVE_WIDTH, WAVE_HEIGHT, 0 },
	{(c_wnd*)&s_resp_wave, ID_MINI_WAV_VIEW_RESP_WAVE, 0, 0, WAVE_HEIGHT * 2,	WAVE_WIDTH, WAVE_HEIGHT, 0 },
	{0,0,0,0,0,0,0}
};
