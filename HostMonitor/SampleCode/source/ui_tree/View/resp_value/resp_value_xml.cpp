#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "../include/ctrl_id.h"
#include "resp_value_xml.h"

static c_value_ctrl s_value_resp;
WND_TREE g_resp_value_view_children[] =
{
	{&s_value_resp, ID_RESP_VIEW_RR_VALUE, 0, 8, 5, 318, 126},
	{NULL,0,0,0,0,0,0}
};
