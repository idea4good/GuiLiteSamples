#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/wave_ctrl.h"
#include "../include/ctrl_id.h"

static c_wave_ctrl s_spo2wavectrl;
WND_TREE g_spo2_wave_view_children[] = 
{
	{&s_spo2wavectrl, ID_MAIN_SCREEN_SPO2_WAVE_CTRL, 0, 3, 5, 673, 159},
	{NULL,0,0,0,0,0,0}
};
