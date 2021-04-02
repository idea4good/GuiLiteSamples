#define GUILITE_ON  //Do not define this macro once more!!!
#include "GuiLite.h"
#include <stdlib.h>
#include <string.h>

const int UI_WIDTH = 238;
const int UI_HEIGHT = 169;
//////////////////////// define widgets & map message ////////////////////////
enum WND_ID
{
	ID_DESKTOP = 1,
	ID_BUTTON
};

extern const BITMAP_INFO frame_00_bmp, frame_01_bmp, frame_02_bmp, frame_03_bmp, frame_04_bmp, frame_05_bmp, frame_06_bmp, frame_07_bmp, frame_08_bmp, frame_09_bmp, frame_10_bmp, frame_11_bmp, frame_12_bmp, frame_13_bmp, frame_14_bmp, frame_15_bmp, frame_16_bmp, frame_17_bmp, frame_18_bmp, frame_19_bmp, frame_20_bmp, frame_21_bmp, frame_22_bmp, frame_23_bmp;

BITMAP_INFO s_frames[] = { frame_00_bmp, frame_01_bmp, frame_02_bmp,  frame_03_bmp,  frame_04_bmp,  frame_05_bmp, frame_06_bmp,  frame_07_bmp,  frame_08_bmp,  frame_09_bmp,  frame_10_bmp,  frame_11_bmp, frame_12_bmp, frame_13_bmp, frame_14_bmp, frame_15_bmp, frame_16_bmp, frame_17_bmp,	frame_18_bmp, frame_19_bmp, frame_20_bmp, frame_21_bmp, frame_22_bmp, frame_23_bmp };


class c_myUI : public c_wnd
{
	virtual void on_init_children()
	{
		c_button* button = (c_button*)get_wnd_ptr(ID_BUTTON);
		button->set_on_click((WND_CALLBACK)&c_myUI::on_clicked);
	}
	virtual void on_paint(void)
	{
		c_rect rect;
		get_screen_rect(rect);
		c_theme::add_image(IMAGE_CUSTOM1, &frame_00_bmp);
		c_image::draw_image(m_surface, m_z_order, c_theme::get_image(IMAGE_CUSTOM1), rect.m_left, rect.m_top);
	}
	void on_clicked(int ctrl_id, int param)
	{
		c_rect rect;
		get_screen_rect(rect);

		for (int i = 0; i < sizeof(s_frames) / sizeof(BITMAP_INFO); i++)
		{
			c_theme::add_image(IMAGE_CUSTOM1, &s_frames[i]);
			c_image::draw_image(m_surface, m_z_order, c_theme::get_image(IMAGE_CUSTOM1), rect.m_left, rect.m_top);
			thread_sleep(60);
		}
	}
};

//////////////////////// layout UI ////////////////////////
static c_myUI s_myUI;
static c_button	s_button;

static WND_TREE s_myUI_children[] =
{
	{(c_wnd*)&s_button, ID_BUTTON, "\xe5\x8f\x98\xe5\xbd\xa2", 0, 149, 40, 20, NULL},
	{ NULL,0,0,0,0,0,0 }
};

//////////////////////// start UI ////////////////////////
extern const LATTICE_FONT_INFO KaiTi_19;
static c_display* s_display;
void load_resource()
{
	//for button
	c_theme::add_font(FONT_DEFAULT, &KaiTi_19);
	c_theme::add_color(COLOR_WND_FONT, GL_RGB(255, 255, 255));
	c_theme::add_color(COLOR_WND_NORMAL, GL_RGB(59, 75, 94));
	c_theme::add_color(COLOR_WND_PUSHED, GL_RGB(33, 42, 53));
	c_theme::add_color(COLOR_WND_FOCUS, GL_RGB(43, 118, 219));
	c_theme::add_color(COLOR_WND_BORDER, GL_RGB(46, 59, 73));
}

void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes)
{
	load_resource();
	c_surface surface = c_surface(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_0);
	s_display = new c_display(phy_fb, screen_width, screen_height, &surface);

	s_myUI.set_surface(&surface);
	s_myUI.connect(NULL, ID_DESKTOP, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_myUI_children);
	s_myUI.show_window();

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

void sendTouch2HelloAnimation(int x, int y, bool is_down)
{
	is_down ? s_myUI.on_touch(x, y, TOUCH_DOWN) : s_myUI.on_touch(x, y, TOUCH_UP);
}

void* getUiOfHelloAnimation(int* width, int* height, bool force_update)
{
	return s_display->get_updated_fb(width, height, force_update);
}

int captureUiOfHelloAnimation()
{
	return s_display->snap_shot("snap_short.bmp");
}