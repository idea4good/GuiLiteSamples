/*
 * root.cpp
 */
#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/msg.h"
#include "core_include/surface.h"
#include "core_include/display.h"
#include "gui_include/slide_group.h"
#include "gui_include/gesture.h"

#include "../include/define.h"
#include "../include/ctrl_id.h"

#include "View/top_bar/top_bar_xml.h"
#include "View/top_bar/top_bar.h"

extern void create_page_main(c_slide_group* group);
extern void create_page_trend(c_slide_group* group);
extern void create_page_main(c_slide_group* group);
extern void create_page_ecg_7wave(c_slide_group* group);
extern void create_page_config(c_slide_group* group);

extern void create_clone_page_config(c_slide_group* group);
extern void create_clone_page_ecg_7wave(c_slide_group* group);
extern void create_clone_page_main(c_slide_group* group);
extern void create_clone_page_trend(c_slide_group* group);

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

static c_slide_root		s_root;
static c_top_bar 		s_top_info_view;
static c_slide_group 	s_slide_group;
//right values region
static c_ecg_value_view		s_param_ecg_view;
static c_spo2_value_view	s_param_spo2_view;
static c_resp_value_view	s_param_resp_view;
static c_nibp_value_view	s_param_nibp_view;

#define	VALUE_VIEW_X			(14 + SCREEN_WIDTH * 2 / 3)
#define	VALUE_VIEW_WIDTH		(SCREEN_WIDTH / 3 - 14)
#define VALUE_VIEW_HEIGHT		((SCREEN_HEIGHT - TOP_BAR_HEIGHT) / 4)

static WND_TREE s_root_children[] =
{
	{ (c_wnd*)&s_top_info_view, ID_TOP_BAR, 0, 0, 0, SCREEN_WIDTH, TOP_BAR_HEIGHT, g_top_view_children },
	//left
	{ (c_wnd*)&s_slide_group, ID_PAGE_GROUP, 0, 0, TOP_BAR_HEIGHT, (SCREEN_WIDTH * 2 / 3), (SCREEN_HEIGHT - TOP_BAR_HEIGHT)},
	//right values
	{ (c_wnd*)&s_param_ecg_view,  ID_ECG_VALUE_VIEW,  0, VALUE_VIEW_X, TOP_BAR_HEIGHT,								VALUE_VIEW_WIDTH, VALUE_VIEW_HEIGHT, g_ecg_value_view_children },
	{ (c_wnd*)&s_param_spo2_view, ID_SPO2_VALUE_VIEW, 0, VALUE_VIEW_X, (TOP_BAR_HEIGHT + VALUE_VIEW_HEIGHT * 1),	VALUE_VIEW_WIDTH, VALUE_VIEW_HEIGHT, g_spo2_value_view_children },
	{ (c_wnd*)&s_param_resp_view, ID_RESP_VALUE_VIEW, 0, VALUE_VIEW_X, (TOP_BAR_HEIGHT + VALUE_VIEW_HEIGHT * 2),	VALUE_VIEW_WIDTH, VALUE_VIEW_HEIGHT, g_resp_value_view_children },
	{ (c_wnd*)&s_param_nibp_view, ID_NIBP_VALUE_VIEW, 0, VALUE_VIEW_X, (TOP_BAR_HEIGHT + VALUE_VIEW_HEIGHT * 3),	VALUE_VIEW_WIDTH, VALUE_VIEW_HEIGHT, g_nibp_value_view_children },
	{	NULL,0,0,0,0,0,0}
};

void load_ui_single(void* phy_fb)
{
	c_display* display = new c_display(phy_fb, SCREEN_WIDTH, SCREEN_HEIGHT, 4);
	c_surface* surface = display->create_surface(&s_root, Z_ORDER_LEVEL_0);
	surface->set_active(true);
	s_root.set_surface(surface);
	s_root.connect(NULL, ID_ROOT, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, s_root_children);

	create_page_ecg_7wave(&s_slide_group);
	create_page_main(&s_slide_group);
	create_page_trend(&s_slide_group);
	create_page_config(&s_slide_group);
	s_slide_group.set_active_slide(1);
	s_root.show_window();

	new c_gesture(&s_root, &s_slide_group, display->get_hid_pipe());
}

void load_ui_multi(void* phy_fb)
{
	c_display* display = new c_display(phy_fb, SCREEN_WIDTH, SCREEN_HEIGHT, 4);
	c_surface* surface = display->create_surface(&s_root, Z_ORDER_LEVEL_0);
	surface->set_active(true);
	s_root.set_surface(surface);
	c_wnd* root = s_root.connect_clone(NULL, ID_ROOT, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, s_root_children);

	c_slide_group* page_group = (c_slide_group*)(root->get_wnd_ptr(ID_PAGE_GROUP));

	create_clone_page_ecg_7wave(page_group);
	create_clone_page_main(page_group);
	create_clone_page_trend(page_group);
	create_clone_page_config(page_group);
	page_group->set_active_slide(1);
	root->show_window();

	new c_gesture(root, page_group, display->get_hid_pipe());
}

/////////////////////// Mini UI ///////////////////////////////////////
#include "ViewMini/value/mini_value_view.h"
#include "ViewMini/value/mini_value_xml.h"

static c_slide_root			s_mini_root;
static c_slide_group 		s_mini_slide_group;
static c_mini_value_view	s_value_view;

static WND_TREE s_mini_root_children[] =
{
	{ (c_wnd*)&s_mini_slide_group, ID_PAGE_GROUP, 0, 0, 0, (MINI_SCREEN_WIDTH * 2 / 3), MINI_SCREEN_HEIGHT },
	{ (c_wnd*)&s_value_view,  ID_MINI_VALUE_VIEW_ID, 0, (MINI_SCREEN_WIDTH * 2 / 3), 0, (MINI_SCREEN_WIDTH * 1 / 3), MINI_SCREEN_HEIGHT, g_mini_wav_value_view_children },
	{ NULL,0,0,0,0,0,0 }
};

extern void create_page_mini_wav(c_slide_group* group);
extern void create_page_mini_trend(c_slide_group* group);

extern void create_clone_page_mini_trend(c_slide_group* group);
extern void create_clone_page_mini_wav(c_slide_group* group);

void load_mini_ui_single(void* phy_fb)
{
	c_display* display = new c_display(phy_fb, MINI_SCREEN_WIDTH, MINI_SCREEN_HEIGHT, 2);
	c_surface* surface = display->create_surface(&s_mini_root, Z_ORDER_LEVEL_0);
	surface->set_active(true);
	s_mini_root.set_surface(surface);
	s_mini_root.connect(NULL, ID_ROOT, 0, 0, 0, MINI_SCREEN_WIDTH, MINI_SCREEN_HEIGHT, s_mini_root_children);

	create_page_mini_wav(&s_mini_slide_group);
	create_page_mini_trend(&s_mini_slide_group);
	s_mini_slide_group.set_active_slide(0);
	s_mini_root.show_window();

	new c_gesture(&s_mini_root, &s_mini_slide_group, display->get_hid_pipe());
}

void load_mini_ui_multi(void* phy_fb)
{
	c_display* display = new c_display(phy_fb, MINI_SCREEN_WIDTH, MINI_SCREEN_HEIGHT, 2);
	c_surface* surface = display->create_surface(&s_mini_root, Z_ORDER_LEVEL_0);
	surface->set_active(true);
	s_mini_root.set_surface(surface);
	c_wnd* root = s_mini_root.connect_clone(NULL, ID_ROOT, 0, 0, 0, MINI_SCREEN_WIDTH, MINI_SCREEN_HEIGHT, s_mini_root_children);

	c_slide_group* page_group = (c_slide_group*)(root->get_wnd_ptr(ID_PAGE_GROUP));

	create_clone_page_mini_wav(page_group);
	create_clone_page_mini_trend(page_group);
	page_group->set_active_slide(0);
	root->show_window();

	new c_gesture(root, page_group, display->get_hid_pipe());
}