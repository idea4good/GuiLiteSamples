#include "../include/GuiLite.h"
#include "../source/ui_ctrl_ex/wave_ctrl_ex.h"
#include "../include/ctrl_id.h"
#include "ecg_wave_xml.h"

static c_ecg_wave_ctrl s_ecg_wave_ctrl;
WND_TREE g_ecg_wave_view_children[] =
{
	{	&s_ecg_wave_ctrl, ID_MAIN_SCREEN_ECG_WAVE_CTRL, 0, 3, 2, 673, 164},
	{	0,0,0,0,0,0,0}
};

