#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/api.h"
#include "core_include/wnd.h"
#include "core_include/msg.h"
#include "core_include/surface.h"
#include "gui_include/dialog.h"
#include "gui_include/slide_group.h"

#include "../include/define.h"
#include "../include/ctrl_id.h"

#include "../source/ui_ctrl_ex/value_view.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"

#include "ViewMini/trend/mini_trend_view.h"
#include "ViewMini/trend/mini_trend_xml.h"

#define TREND_WIDTH 		(MINI_SCREEN_WIDTH * 2 / 3)
#define TREND_HEIGHT		MINI_SCREEN_HEIGHT

static c_trend_view_mini 	s_trend_view;
static c_slide_root			s_root;

static WND_TREE g_trend_page_children[] =
{
	{ (c_wnd*)&s_trend_view,  ID_TREND_SCREEN_TREND, 0, 0, 0, TREND_WIDTH, TREND_HEIGHT, g_mini_trend_view_children},
	{ NULL,0,0,0,0,0,0 }
};

void create_page_mini_trend(c_slide_group* group)
{
	group->add_slide(&s_root, ID_PAGE_TREND, 0, 0, TREND_WIDTH, TREND_HEIGHT, g_trend_page_children);
}

void create_clone_page_mini_trend(c_slide_group* group)
{
	group->add_clone_silde(&s_root, ID_PAGE_TREND, 0, 0, TREND_WIDTH, TREND_HEIGHT, g_trend_page_children);
}
