#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/api.h"
#include "core_include/wnd.h"
#include "core_include/surface.h"
#include "gui_include/slide_group.h"

#include "../include/define.h"
#include "../include/ctrl_id.h"

#include "../source/ui_ctrl_ex/value_view.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "../source/manager/wave_manager.h"

#include "View/ecg_wave/ecg_wave_view.h"
#include "View/ecg_wave/ecg_wave_xml.h"
#include "View/resp_wave/resp_wave_view.h"
#include "View/resp_wave/resp_wave_xml.h"
#include "View/spo2_wave/spo2_wave_view.h"
#include "View/spo2_wave/spo2_wave_xml.h"

#include "View/temp_value/temp_value_view.h"
#include "View/temp_value/temp_value_xml.h"
#include "View/nibp_list/nibp_list_view.h"
#include "View/nibp_list/nibp_list_xml.h"

#define PAGE_WIDTH		(SCREEN_WIDTH * 2 / 3)
#define PAGE_HEIGHT		(SCREEN_HEIGHT - TOP_BAR_HEIGHT)
#define WAVE_WIDTH 		PAGE_WIDTH
#define WAVE_HEIGHT 	(PAGE_HEIGHT / 4)

//wave
static c_ecg_wave_view   s_wave_ecg_view;
static c_spo2_wave_view  s_wave_spo2_view;
static c_resp_wave_view  s_wave_resp_view;
//temp value
static c_temp_value_view s_param_temp_view;
static c_nibplist_view 	 s_nibp_list_view;

static c_slide_root s_root;
static WND_TREE s_root_normal_children[] =
{
	//wave
	{(c_wnd*)&s_wave_ecg_view, ID_MAIN_PAGE_ECG_WAVE,		0,	0,					0,					WAVE_WIDTH,			WAVE_HEIGHT, g_ecg_wave_view_children},
	{(c_wnd*)&s_wave_spo2_view, ID_MAIN_PAGE_SPO2_WAVE,	0,	0,					WAVE_HEIGHT,		WAVE_WIDTH,			WAVE_HEIGHT, g_spo2_wave_view_children},
	{(c_wnd*)&s_wave_resp_view, ID_MAIN_PAGE_RESP_WAVE,	0,	0,					(WAVE_HEIGHT * 2),	WAVE_WIDTH,			WAVE_HEIGHT, g_resp_wave_view_children},
	//temp & nibp list
	{(c_wnd*)&s_param_temp_view, ID_TEMP_VALUE_VIEW,		0,	0,					(WAVE_HEIGHT * 3),	(WAVE_WIDTH / 2),	WAVE_HEIGHT, g_temp_value_view_children},
	{(c_wnd*)&s_nibp_list_view, ID_NIBP_LIST_VALUE_VIEW,	0,	(WAVE_WIDTH / 2),	(WAVE_HEIGHT * 3),	(WAVE_WIDTH / 2),	WAVE_HEIGHT, g_nibp_list_view_children},
	{NULL,0,0,0,0,0,0 }
};

void create_page_main(c_slide_group* group)
{
	group->add_slide(&s_root, ID_PAGE_MAIN, 0, 0, PAGE_WIDTH, PAGE_HEIGHT, s_root_normal_children);
}

void create_clone_page_main(c_slide_group* group)
{
	group->add_clone_silde(&s_root, ID_PAGE_MAIN, 0, 0, PAGE_WIDTH, PAGE_HEIGHT, s_root_normal_children);
}
