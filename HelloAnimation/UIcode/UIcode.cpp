#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/surface.h"
#include "core_include/resource.h"
#include "core_include/bitmap.h"
#include "core_include/word.h"
#include "core_include/msg.h"
#include "core_include/display.h"
#include "gui_include/my_resource.h"
#include "gui_include/button.h"
#include "gui_include/slide_group.h"
#include "gui_include/gesture.h"
#include <stdlib.h>
#include <string.h>

const int UI_WIDTH = 238;
const int UI_HEIGHT = 169;
//////////////////////// define widgets & map message ////////////////////////
enum WND_ID
{
	ID_ROOT = 1,
	ID_DESKTOP,
	ID_BUTTON
};
class c_root : public c_wnd
{
	virtual c_wnd* clone() { return new c_root(); }
};

class c_myUI : public c_wnd
{
	virtual c_wnd* clone() { return new c_myUI(); }
	virtual void on_paint(void);
	void on_clicked(unsigned int ctrl_id);
	GL_DECLARE_MESSAGE_MAP()//delcare message
};

//map message
GL_BEGIN_MESSAGE_MAP(c_myUI)
ON_GL_BN_CLICKED(ID_BUTTON, c_myUI::on_clicked)
GL_END_MESSAGE_MAP()

extern const BITMAP_INFO frame_00_bmp, frame_01_bmp, frame_02_bmp, frame_03_bmp, frame_04_bmp, frame_05_bmp, frame_06_bmp,
frame_07_bmp, frame_08_bmp, frame_09_bmp, frame_10_bmp, frame_11_bmp, frame_12_bmp, frame_13_bmp, frame_14_bmp,
frame_15_bmp, frame_16_bmp, frame_17_bmp, frame_18_bmp, frame_19_bmp, frame_20_bmp, frame_21_bmp, frame_22_bmp, frame_23_bmp;

BITMAP_INFO s_frames[] = { frame_00_bmp, frame_01_bmp, frame_02_bmp,  frame_03_bmp,  frame_04_bmp,  frame_05_bmp,
							frame_06_bmp,  frame_07_bmp,  frame_08_bmp,  frame_09_bmp,  frame_10_bmp,  frame_11_bmp, 
							frame_12_bmp, frame_13_bmp, frame_14_bmp, frame_15_bmp, frame_16_bmp, frame_17_bmp,
							frame_18_bmp, frame_19_bmp, frame_20_bmp, frame_21_bmp, frame_22_bmp, frame_23_bmp };
void c_myUI::on_clicked(unsigned int ctrl_id)
{
	c_rect rect;
	get_screen_rect(rect);

	for (int i = 0; i < sizeof(s_frames)/sizeof(BITMAP_INFO); i++)
	{
		c_my_resource::add_bitmap(BITMAP_CUSTOM1, &s_frames[i]);
		c_bitmap::draw_bitmap(m_surface, m_z_order, c_my_resource::get_bmp(BITMAP_CUSTOM1), rect.m_left, rect.m_top);
		thread_sleep(60);
	}
}

void c_myUI::on_paint()
{
	c_rect rect;
	get_screen_rect(rect);
	c_my_resource::add_bitmap(BITMAP_CUSTOM1, &frame_00_bmp);
	c_bitmap::draw_bitmap(m_surface, m_z_order, c_my_resource::get_bmp(BITMAP_CUSTOM1), rect.m_left, rect.m_top);
}

//////////////////////// layout UI ////////////////////////
static c_root s_root;
static c_myUI s_myUI;
static c_button	s_button;

static WND_TREE s_myUI_children[] =
{
	{(c_wnd*)&s_button, ID_BUTTON, "\xe5\x8f\x98\xe5\xbd\xa2", 0, 149, 40, 20, NULL},
	{ NULL,0,0,0,0,0,0 }
};

static WND_TREE s_root_children[] =
{
	//start button
	{(c_wnd*)&s_myUI, ID_DESKTOP, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_myUI_children},
	{ NULL,0,0,0,0,0,0 }
};

//////////////////////// start UI ////////////////////////
extern const FONT_INFO KaiTi_19;
static c_fifo s_hid_fifo;
static c_display* s_display;
void load_resource()
{
	c_my_resource::add_font(FONT_DEFAULT, &KaiTi_19);//for button
	c_my_resource::add_color(WND_FORECOLOR, GL_RGB(36, 36, 36));//for button
	c_my_resource::add_color(WND_BACKCOLOR, GL_RGB(255, 255, 255));//for button
}

void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes)
{
	load_resource();
	s_display = new c_display(phy_fb, screen_width, screen_height, UI_WIDTH, UI_HEIGHT, color_bytes, 1);
	c_surface* surface = s_display->alloc_surface(&s_root, Z_ORDER_LEVEL_1);
	surface->set_active(true);

	s_root.set_surface(surface);
	s_root.connect(NULL, ID_ROOT, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_root_children);
	s_root.show_window();

	new c_gesture(&s_root, NULL, &s_hid_fifo);
	while (1)
	{
		thread_sleep(1000000);
	}
}

//////////////////////// interface for all platform ////////////////////////
void startHelloAnimation(void* phy_fb, int width, int height, int color_bytes)
{
	create_ui(phy_fb, width, height, color_bytes);
}

int sendTouch2HelloAnimation(void* buf, int len)
{
	ASSERT(len == sizeof(MSG_INFO));
	return s_hid_fifo.write(buf, len);
}

void* getUiOfHelloAnimation(int* width, int* height, bool force_update)
{
	return s_display->get_updated_fb(width, height, force_update);
}

int captureUiOfHelloAnimation()
{
	return s_display->snap_shot("snap_short.bmp");
}