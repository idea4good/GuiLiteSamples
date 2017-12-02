#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "gui_include/table.h"
#include "../source/ui_ctrl_ex/trend_table.h"
#include "../source/ui_ctrl_ex/trend_graph.h"
#include "../source/ui_ctrl_ex/time_bar.h"
#include "../include/define.h"
#include "../include/ctrl_id.h"
#include "mini_trend_xml.h"

#define WIDHT			(MINI_SCREEN_WIDTH * 2 / 3)
#define	HEIGHT			MINI_SCREEN_HEIGHT

static c_trend_graph s_trend_ctrl_vitals ;

WND_TREE g_mini_trend_view_children[] =
{
	{(c_wnd*)&s_trend_ctrl_vitals, ID_TREND_SCREEN_VITAL_TREND_CTRL, 0, 0, 0, WIDHT, HEIGHT, NULL},
	{0,0,0,0,0,0,0,0}
};
