#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/api.h"
#include "core_include/wnd.h"
#include "core_include/msg.h"
#include "core_include/surface.h"
#include "gui_include/dialog.h"
#include "gui_include/slide_group.h"
#include "gui_include/table.h"

#include "../include/define.h"
#include "../include/ctrl_id.h"
#include "../resource/font/strings.h"

#include "../source/ui_ctrl_ex/time_bar.h"
#include "../source/ui_ctrl_ex/trend_table.h"
#include "../source/ui_ctrl_ex/trend_graph.h"
#include "View/trend/trend_view.h"

#define	PAGE_WIDTH			(SCREEN_WIDTH * 2 / 3)
#define PAGE_HEIGHT			(SCREEN_HEIGHT - TOP_BAR_HEIGHT)

#define	TABLE_WIDTH			(PAGE_WIDTH - 23)
#define	TREND_WIDTH			(PAGE_WIDTH - 25)
#define	TIME_BAR_WIDTH		(PAGE_WIDTH - 17)

#define TABLE_HEIGHT		269
#define	TIME_BAR_HEIGHT		48

#define TABLE_Y				12
#define TREND_HEIGHT		((PAGE_HEIGHT - TABLE_HEIGHT - TIME_BAR_HEIGHT - TABLE_Y - 2 - 2 - 4 - 10) / 2)//10: make frame line include time bar.

#define	VITAL_TREND_Y		(TABLE_Y + TABLE_HEIGHT + 2)
#define	PRESSURE_TREND_Y	(VITAL_TREND_Y + TREND_HEIGHT + 2)
#define	TIME_BAR_Y			(PRESSURE_TREND_Y + TREND_HEIGHT + 4)

static c_trend_table	s_table;
static c_trend_graph	s_trend_vitals;
static c_trend_graph	s_trend_pressure;
static c_time_bar		s_time_bar;

WND_TREE g_page_trend_view_children[] =
{
	{(c_wnd*)&s_table,			ID_TREND_SCREEN_TABLE_CTRL,			0,	18,	TABLE_Y,			TABLE_WIDTH,	TABLE_HEIGHT},
	{(c_wnd*)&s_trend_vitals,	ID_TREND_SCREEN_VITAL_TREND_CTRL,	0,	20,	VITAL_TREND_Y,		TREND_WIDTH,	TREND_HEIGHT},
	{(c_wnd*)&s_trend_pressure,ID_TREND_SCREEN_PRESSURE_CTRL,		0,	20,	PRESSURE_TREND_Y,	TREND_WIDTH,	TREND_HEIGHT},
	{(c_wnd*)&s_time_bar,		ID_TREND_SCREEN_TIME_SCALE_BAR_CTRL,0,	16,	TIME_BAR_Y,			TIME_BAR_WIDTH,	TIME_BAR_HEIGHT},
	{NULL,0,0,0,0,0,0,0 }
};

static c_trend_view 	s_trend_view;
static c_slide_root		s_root;

WND_TREE g_trend_page_children[]=
{
	{ (c_wnd*)&s_trend_view,  ID_TREND_SCREEN_TREND, 0, 0, 0, PAGE_WIDTH, PAGE_HEIGHT, g_page_trend_view_children},
	{ NULL,0,0,0,0,0,0 }
};

void create_page_trend(c_slide_group* group)
{
	group->add_slide(&s_root, ID_PAGE_TREND, 0, 0, PAGE_WIDTH, PAGE_HEIGHT, g_trend_page_children);
}

void create_clone_page_trend(c_slide_group* group)
{
	group->add_clone_silde(&s_root, ID_PAGE_TREND, 0, 0, PAGE_WIDTH, PAGE_HEIGHT, g_trend_page_children);
}
