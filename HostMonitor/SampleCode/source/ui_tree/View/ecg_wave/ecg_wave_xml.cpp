#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/wave_ctrl.h"
#include "../source/ui_ctrl_ex/ecg_wave_ctrl.h"
#include "../include/ctrl_id.h"
#include "ecg_wave_xml.h"

static c_ecg_wave_ctrl s_ecg_wave_ctrl;
WND_TREE g_ecg_wave_view_children[] =
{
	{	&s_ecg_wave_ctrl, ID_MAIN_SCREEN_ECG_WAVE_CTRL, 0, 3, 2, 673, 164},
	{	NULL,0,0,0,0,0,0}
};

