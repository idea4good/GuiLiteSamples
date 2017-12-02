#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "gui_include/label.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "../include/ctrl_id.h"
#include "spo2_value_xml.h"

static c_value_ctrl s_value_spo2, s_value_pr;
static c_label s_bar;
static c_label s_prsource;

WND_TREE g_spo2_value_view_children[] =
{
	{&s_value_spo2,		ID_SPO2_VIEW_SPO2_VALUE,	0,    	8,		5,		168,		126},
	{&s_value_pr,		ID_SPO2_VIEW_PR_VALUE,		0,      208,	5,		112,		126},
	{NULL,0,0,0,0,0,0}
};
