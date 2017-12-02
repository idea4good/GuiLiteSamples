#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "gui_include/label.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "../source/ui_ctrl_ex/value_sub_ctrl.h"
#include "../include/ctrl_id.h"
#include "../source/resource/font/strings.h"
#include "mini_value_xml.h"

static c_value_sub_ctrl s_hr_value_wav;
static c_value_sub_ctrl s_spo2_value_wav;
static c_value_sub_ctrl s_resp_value_wav;

WND_TREE g_mini_wav_value_view_children[] =
{
	{ &s_hr_value_wav,		ID_MINI_VALUE_VIEW_HR_VALUE,	0, 8,	5,	 130, 100 },
	{ &s_resp_value_wav,	ID_MINI_VALUE_VIEW_RESP_VALUE,	0, 200,	5,	 130, 100 },
	{ &s_spo2_value_wav,	ID_MINI_VALUE_VIEW_SPO2_VALUE,	0, 8,	165, 130, 100 },
	{ NULL,0,0,0,0,0,0 }
};
