#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/wave_ctrl.h"
#include "../include/ctrl_id.h"

static c_wave_ctrl s_resp_wavectrl;
WND_TREE g_resp_wave_view_children[] = 
{
	{&s_resp_wavectrl,ID_MAIN_SCREEN_RESP_WAVE_CTRL,0,	3,	5,	673,	159},
	{NULL,0,0,0,0,0,0}
};
