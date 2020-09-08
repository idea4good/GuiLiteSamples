/*
 * root.cpp
 */
#include <stdio.h>
#include <string.h>
#include "../include/GuiLite.h"
#include "../include/define.h"
#include "../include/ctrl_id.h"

#include "View/top_bar/top_bar_xml.h"
#include "View/top_bar/top_bar.h"

extern void create_page_main(c_slide_group* group);
extern void create_page_trend(c_slide_group* group);
extern void create_page_main(c_slide_group* group);
extern void create_page_ecg_7wave(c_slide_group* group);
extern void create_page_config(c_slide_group* group);

/////////////////////// Standard UI ///////////////////////////////////////
#include "../source/ui_ctrl_ex/value_view.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "View/ecg_value/ecg_value_view.h"
#include "View/ecg_value/ecg_value_xml.h"
#include "View/spo2_value/spo2_value_view.h"
#include "View/spo2_value/spo2_value_xml.h"
#include "View/resp_value/resp_value_view.h"
#include "View/resp_value/resp_value_xml.h"
#include "View/nibp_value/nibp_value_view.h"
#include "View/nibp_value/nibp_value_xml.h"

static c_display*		s_display;
static c_wnd			s_root;
static c_top_bar 		s_top_info_view;
static c_slide_group 	s_slide_group;
//right values region
static c_ecg_value_view		s_param_ecg_view;
static c_spo2_value_view	s_param_spo2_view;
static c_resp_value_view	s_param_resp_view;
static c_nibp_value_view	s_param_nibp_view;

#define	VALUE_VIEW_X			(14 + UI_WIDTH * 2 / 3)
#define	VALUE_VIEW_WIDTH		(UI_WIDTH / 3 - 14)
#define VALUE_VIEW_HEIGHT		((UI_HEIGHT - TOP_BAR_HEIGHT) / 4)

static WND_TREE s_root_children[] =
{
	{ (c_wnd*)&s_top_info_view, ID_TOP_BAR, 0, 0, 0, UI_WIDTH, TOP_BAR_HEIGHT, g_top_view_children },
	//left
	{ (c_wnd*)&s_slide_group, ID_PAGE_GROUP, 0, 0, TOP_BAR_HEIGHT, (UI_WIDTH * 2 / 3), (UI_HEIGHT - TOP_BAR_HEIGHT)},
	//right values
	{ (c_wnd*)&s_param_ecg_view,  ID_ECG_VALUE_VIEW,  0, VALUE_VIEW_X, TOP_BAR_HEIGHT,								VALUE_VIEW_WIDTH, VALUE_VIEW_HEIGHT, g_ecg_value_view_children },
	{ (c_wnd*)&s_param_spo2_view, ID_SPO2_VALUE_VIEW, 0, VALUE_VIEW_X, (TOP_BAR_HEIGHT + VALUE_VIEW_HEIGHT * 1),	VALUE_VIEW_WIDTH, VALUE_VIEW_HEIGHT, g_spo2_value_view_children },
	{ (c_wnd*)&s_param_resp_view, ID_RESP_VALUE_VIEW, 0, VALUE_VIEW_X, (TOP_BAR_HEIGHT + VALUE_VIEW_HEIGHT * 2),	VALUE_VIEW_WIDTH, VALUE_VIEW_HEIGHT, g_resp_value_view_children },
	{ (c_wnd*)&s_param_nibp_view, ID_NIBP_VALUE_VIEW, 0, VALUE_VIEW_X, (TOP_BAR_HEIGHT + VALUE_VIEW_HEIGHT * 3),	VALUE_VIEW_WIDTH, VALUE_VIEW_HEIGHT, g_nibp_value_view_children },
	{	0,0,0,0,0,0,0}
};

void load_ui_single(void* phy_fb, int width, int height, int color_bytes)
{
	s_display = new c_display(phy_fb, width, height, UI_WIDTH, UI_HEIGHT, color_bytes, (4 + 1));//4 slides + 1 root
	c_surface* surface = s_display->alloc_surface(Z_ORDER_LEVEL_0);
	surface->set_active(true);
	s_root.set_surface(surface);
	s_root.connect(0, ID_ROOT, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_root_children);

	create_page_ecg_7wave(&s_slide_group);
	create_page_main(&s_slide_group);
	create_page_trend(&s_slide_group);
	create_page_config(&s_slide_group);
	s_slide_group.set_active_slide(1);
	s_root.show_window();
}

void sendTouch2HostMonitor(int x, int y, bool is_down)
{
	is_down ? s_root.on_touch(x, y, TOUCH_DOWN) : s_root.on_touch(x, y, TOUCH_UP);
}

void* getUiOfHostMonitor(int* width, int* height, bool force_update)
{
	if(!s_display)
	{
		return 0;
	}
	return s_display->get_updated_fb(width, height, force_update);
}

int captureUiOfHostMonitor(int display_id)
{
	char file_name[32];
	memset(file_name, 0, sizeof(file_name));
	sprintf(file_name, "snapshot_%d.bmp", display_id);
	return s_display->snap_shot(file_name);
}

//Cloud API
typedef int(*SYNC_DATA)(int hr, int spo2, int rr, int nibp_sys, int nibp_dia, int nibp_mean);
SYNC_DATA gSyncData;