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
#include "gui_include/dialog.h"
#include "gui_include/gesture.h"
#include <stdlib.h>
#include <string.h>

const int UI_WIDTH = 1400;
const int UI_HEIGHT = 580;

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

#ifdef WIN32
//For Visual studio, one chinese character need 3 UTF-8 bytes
static const char* s_text = "\xe6\x9c\x9d\xe8\xbe\x9e\xe7\x99\xbd\xe5\xb8\x9d\xe5\xbd\xa9\xe4\xba\x91\xe9\x97\xb4\xe5\x8d\x83\xe9\x87\x8c\xe6\xb1\x9f\xe9\x99\xb5\xe4\xb8\x80\xe6\x97\xa5\xe8\xbf\x98\xe4\xb8\xa4\xe5\xb2\xb8\xe7\x8c\xbf\xe5\xa3\xb0\xe5\x95\xbc\xe4\xb8\x8d\xe4\xbd\x8f\xe8\xbd\xbb\xe8\x88\x9f\xe5\xb7\xb2\xe8\xbf\x87\xe4\xb8\x87\xe9\x87\x8d\xe5\xb1\xb1";
#else
//For Unix, all chinese charaters would be encoded in UTF-8 perfectly.
static const char* s_text = "朝辞白帝彩云间千里江陵一日还两岸猿声啼不住轻舟已过万重山";
#endif
#define FONT_SIZE	57
#define START_X		300
#define START_Y		20
void c_myUI::on_clicked(unsigned int ctrl_id)
{
	c_rect rect;
	get_screen_rect(rect);
	c_bitmap::draw_bitmap(m_surface, m_z_order, c_my_resource::get_bmp(BITMAP_CUSTOM1), rect.m_left, rect.m_top);

	char one_word[4];
	const char* tmp = s_text;
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 7; y++)
		{
			memset(one_word, 0, sizeof(one_word));
			memcpy(one_word, tmp, 3);
			c_word::draw_string(m_surface, m_z_order, one_word, (START_X - x * FONT_SIZE), (START_Y + y * FONT_SIZE), c_my_resource::get_font(FONT_DEFAULT), GL_RGB(0, 0, 0), GL_ARGB(0, 0, 0, 0));
			thread_sleep(500);
			tmp += 3;
		}
}

void c_myUI::on_paint()
{
	c_rect rect;
	get_screen_rect(rect);
	c_bitmap::draw_bitmap(m_surface, m_z_order, c_my_resource::get_bmp(BITMAP_CUSTOM1), rect.m_left, rect.m_top);
}

//////////////////////// layout UI ////////////////////////
static c_root s_root;
static c_myUI s_myUI;
static c_button	s_button;

static WND_TREE s_myUI_children[] =
{
	{(c_wnd*)&s_button, ID_BUTTON, "PLAY", 0, 540, 150, 40, NULL},
	{ NULL,0,0,0,0,0,0 }
};

static WND_TREE s_root_children[] =
{
	//start button
	{(c_wnd*)&s_myUI, ID_DESKTOP, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_myUI_children},
	{ NULL,0,0,0,0,0,0 }
};

//////////////////////// start UI ////////////////////////
extern const BITMAP_INFO background_bmp;
extern const FONT_INFO KaiTi_33B;
static c_fifo s_hid_fifo;
static c_display* s_display;
void load_resource()
{
	c_my_resource::add_bitmap(BITMAP_CUSTOM1, &background_bmp);
	c_my_resource::add_font(FONT_DEFAULT, &KaiTi_33B);//for button
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
	while(1)
	{
		thread_sleep(1000000);
	}
}

//////////////////////// interface for all platform ////////////////////////
void startHelloFont(void* phy_fb, int width, int height, int color_bytes)
{
	create_ui(phy_fb, width, height, color_bytes);
}

int sendTouch2HelloFont(void* buf, int len)
{
	ASSERT(len == sizeof(MSG_INFO));
	return s_hid_fifo.write(buf, len);
}

void* getUiOfHelloFont(int* width, int* height, bool force_update)
{
	return s_display->get_updated_fb(width, height, force_update);
}

int captureUiOfHelloFont()
{
	return s_display->snap_shot("snap_short.bmp");
}