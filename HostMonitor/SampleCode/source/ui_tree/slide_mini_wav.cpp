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
#include "ViewMini/wav/mini_wave_view.h"
#include "ViewMini/wav/mini_wave_xml.h"

#define WAVE_WIDTH 		(MINI_SCREEN_WIDTH * 2 / 3)
#define WAVE_HEIGHT 	MINI_SCREEN_HEIGHT

static c_mini_wave_view		s_wave_view;
static c_slide_root s_root;
static WND_TREE s_root_normal_children[] =
{
	{ (c_wnd*)&s_wave_view, ID_MINI_WAV_VIEW_ID, 0, 0, 0, WAVE_WIDTH, WAVE_HEIGHT, g_mini_wave_view_children },
	{ NULL,0,0,0,0,0,0 }
};

void create_page_mini_wav(c_slide_group* group)
{
	group->add_slide(&s_root, ID_PAGE_MAIN, 0, 0, WAVE_WIDTH, WAVE_HEIGHT, s_root_normal_children);
}

void create_clone_page_mini_wav(c_slide_group* group)
{
	group->add_clone_silde(&s_root, ID_PAGE_MAIN, 0, 0, WAVE_WIDTH, WAVE_HEIGHT, s_root_normal_children);
}
