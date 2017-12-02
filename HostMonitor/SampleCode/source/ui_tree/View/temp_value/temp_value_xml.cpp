#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "../source/ui_ctrl_ex/value_sub_ctrl.h"
#include "../include/ctrl_id.h"
#include "../source/resource/font/strings.h"
#include "temp_value_xml.h"

static c_value_ctrl		s_value_temp_t1;
static c_value_sub_ctrl s_value_temp_t2;
static c_value_sub_ctrl s_value_temp_td;

WND_TREE g_temp_value_view_children[] =
{
	{&s_value_temp_t1, ID_TEMP_VIEW_T1_VALUE,	STR_TEMP_T1, 8,		2,	202, 127},
	{&s_value_temp_t2, ID_TEMP_VIEW_T2_VALUE,	STR_TEMP_T2, 210,	2,	113, 66},
	{&s_value_temp_td, ID_TEMP_VIEW_TD_VALUE,	STR_TEMP_TD, 210,	68,	113, 65},
	{NULL,0,0,0,0,0,0}
};
