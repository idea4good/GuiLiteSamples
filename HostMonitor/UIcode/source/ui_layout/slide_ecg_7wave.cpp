#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/api.h"
#include "../core_include/wnd.h"
#include "../core_include/surface.h"
#include "../core_include/display.h"
#include "../widgets_include/dialog.h"
#include "../widgets_include/slide_group.h"
#include "../widgets_include/wave_buffer.h"
#include "../widgets_include/wave_ctrl.h"

#include "../include/define.h"
#include "../include/ctrl_id.h"

#include "../source/ui_ctrl_ex/wave_ctrl_ex.h"
#include "View/ecg_7wave/ecg_7wave_view.h"

#define PAGE_WIDTH			(UI_WIDTH * 2 / 3)
#define PAGE_HEIGHT			(UI_HEIGHT - TOP_BAR_HEIGHT)
#define WAVE_WIDTH			(PAGE_WIDTH - 9)
#define WAVE_HEIGHT			(PAGE_HEIGHT / 7 )

class c_slide_root : public c_wnd
{
	virtual c_wnd* clone() { return new c_slide_root(); }
};

static c_ecg_wave_ctrl    s_wave_1;
static c_ecg_wave_ctrl    s_wave_2;
static c_ecg_wave_ctrl    s_wave_3;
static c_ecg_wave_ctrl    s_wave_4;
static c_ecg_wave_ctrl    s_wave_5;
static c_ecg_wave_ctrl    s_wave_6;
static c_ecg_wave_ctrl    s_wave_7;

static WND_TREE s_view_children[] =
{
	{ (c_wnd*)&s_wave_1, ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE1,   0,   0,    0,				   WAVE_WIDTH,	 WAVE_HEIGHT },
	{ (c_wnd*)&s_wave_2, ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE2,   0,   0,    (WAVE_HEIGHT * 1),   WAVE_WIDTH,   WAVE_HEIGHT },
	{ (c_wnd*)&s_wave_3, ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE3,   0,   0,    (WAVE_HEIGHT * 2),   WAVE_WIDTH,   WAVE_HEIGHT },
	{ (c_wnd*)&s_wave_4, ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE4,   0,   0,    (WAVE_HEIGHT * 3),   WAVE_WIDTH,   WAVE_HEIGHT },
	{ (c_wnd*)&s_wave_5, ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE5,   0,   0,    (WAVE_HEIGHT * 4),   WAVE_WIDTH,   WAVE_HEIGHT },
	{ (c_wnd*)&s_wave_6, ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE6,   0,   0,    (WAVE_HEIGHT * 5),   WAVE_WIDTH,   WAVE_HEIGHT },
	{ (c_wnd*)&s_wave_7, ID_ECG_FULL_SCREEN_VIEW_ECG_WAVE7,   0,   0,    (WAVE_HEIGHT * 6),   WAVE_WIDTH,   WAVE_HEIGHT },
	{ 0,0,0,0,0,0,0 }
};

static c_ecg_7wave_screen_view	s_ecg_7wave_view;
static c_slide_root				s_root;

static WND_TREE s_children[]=
{
	{   &s_ecg_7wave_view, ID_ECG_FULL_SCREEN_VIEW_ID, 0, 0, 0, PAGE_WIDTH,  PAGE_HEIGHT, s_view_children },
	{	0,0,0,0,0,0,0}
};

void create_page_ecg_7wave(c_slide_group* group)
{
	group->add_slide(&s_root, ID_PAGE_ECG_7WAVE, 0, 0, PAGE_WIDTH, PAGE_HEIGHT, s_children);
}

void create_clone_page_ecg_7wave(c_slide_group* group)
{
	group->add_clone_silde(&s_root, ID_PAGE_ECG_7WAVE, 0, 0, PAGE_WIDTH, PAGE_HEIGHT, s_children);
}
