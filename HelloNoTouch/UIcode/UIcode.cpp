#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/surface.h"
#include "core_include/resource.h"
#include "core_include/word.h"
#include "core_include/msg.h"
#include "core_include/display.h"
#include "core_include/theme.h"
#include "widgets_include/label.h"
#include "widgets_include/button.h"
#include <stdlib.h>
#include <stdio.h>

const int UI_WIDTH = 240;
const int UI_HEIGHT = 320;

//////////////////////// define widgets & map message ////////////////////////
enum WND_ID
{
	ID_ROOT = 1,
	ID_LABEL1,
	ID_LABEL2,
	ID_LABEL3,
	ID_BUTTON1,
	ID_BUTTON2,
	ID_BUTTON3
};

class c_myUI : public c_wnd
{
	virtual c_wnd* clone() { return new c_myUI(); }
	virtual void on_paint(void)
	{
		c_rect rect;
		get_screen_rect(rect);
		m_surface->fill_rect(rect, GL_RGB(0, 0, 0), m_z_order);
	}
	void on_clicked(unsigned int ctrl_id) {
		static int sum1, sum2, sum3;
		static char str1[8], str2[8], str3[8];
		c_button* button = (c_button*)get_wnd_ptr(ctrl_id);
		switch (ctrl_id)
		{
		case ID_BUTTON1:
			sprintf(str1, "%d", ++sum1);
			button->set_str(str1);
			break;
		case ID_BUTTON2:
			sprintf(str2, "%d", ++sum2);
			button->set_str(str2);
			break;
		case ID_BUTTON3:
			sprintf(str3, "%d", ++sum3);
			button->set_str(str3);
			break;
		}
		button->show_window();
	}
	GL_DECLARE_MESSAGE_MAP()//delcare message
};

//map message
GL_BEGIN_MESSAGE_MAP(c_myUI)
ON_GL_BN_CLICKED(ID_BUTTON1, c_myUI::on_clicked)
ON_GL_BN_CLICKED(ID_BUTTON2, c_myUI::on_clicked)
ON_GL_BN_CLICKED(ID_BUTTON3, c_myUI::on_clicked)
GL_END_MESSAGE_MAP()

//////////////////////// layout UI ////////////////////////
static c_myUI s_myUI;
static c_label s_label1, s_label2, s_label3;
static c_button s_button1, s_button2, s_button3;
static WND_TREE s_myUI_children[] =
{
	{&s_label1, ID_LABEL1, "a: <<", 20, 20, 80, 40, NULL},
	{&s_label2, ID_LABEL2, "d: >>", 20, 140, 80, 40, NULL},
	{&s_label3, ID_LABEL3, "s: click", 20, 260, 80, 40, NULL},

	{&s_button1, ID_BUTTON1, "0", 140, 20, 80, 40, NULL},
	{&s_button2, ID_BUTTON2, "0", 140, 140, 80, 40, NULL},
	{&s_button3, ID_BUTTON3, "0", 140, 260, 80, 40, NULL},
	{ NULL,0,0,0,0,0,0 }
};

//////////////////////// start UI ////////////////////////
extern const FONT_INFO Consolas_28;
void load_resource()
{
	c_theme::add_font(FONT_DEFAULT, &Consolas_28);
	//for button
	c_theme::add_color(COLOR_WND_FONT, GL_RGB(0, 0, 0));
	c_theme::add_color(COLOR_WND_NORMAL, GL_RGB(255, 255, 255));
	c_theme::add_color(COLOR_WND_PUSHED, GL_RGB(128, 128, 128));
	c_theme::add_color(COLOR_WND_FOCUS, GL_RGB(0, 255, 0));
	c_theme::add_color(COLOR_WND_BORDER, GL_RGB(0, 255, 0));
}

static c_display* s_display;
void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op)
{
	load_resource();
	s_display = new c_display(phy_fb, screen_width, screen_height, UI_WIDTH, UI_HEIGHT, color_bytes, 1, gfx_op);
	c_surface* surface = s_display->alloc_surface(&s_myUI, Z_ORDER_LEVEL_0);
	surface->set_active(true);
	s_myUI.set_surface(surface);
	s_myUI.connect(NULL, ID_ROOT, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_myUI_children);
	s_myUI.show_window();
}

//////////////////////// interface for all platform ////////////////////////
extern "C" void startHelloNoTouch(void* phy_fb, int width, int height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op)
{
	create_ui(phy_fb, width, height, color_bytes, gfx_op);
}

extern "C" void sendTouch2HelloNoTouch(int x, int y, bool is_down)
{
	is_down ? s_myUI.on_touch(x, y, TOUCH_DOWN) : s_myUI.on_touch(x, y, TOUCH_UP);
}

extern "C" void sendKey2HelloNoTouch(unsigned int key)
{
	s_myUI.on_key(KEY_TYPE(key));
}

int captureUiOfHelloNoTouch()
{
	return s_display->snap_shot("snap_short.bmp");
}
