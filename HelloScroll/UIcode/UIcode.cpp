#include <stdio.h>
#define GUILITE_ON	//Do not define this macro once more!!!
#include "GuiLite.h"
#include "scroll.h"

#define UI_WIDTH	600
#define UI_HEIGHT	400

static c_display* s_display;

enum WND_ID
{
	ID_ROOT = 1,
	ID_SCROLL_VIEW_1,
	ID_SCROLL_VIEW_2,
	ID_BUTTON_1,
	ID_BUTTON_2,
	ID_BUTTON_3,
	ID_BUTTON_4,
	ID_BUTTON_5,
	ID_BUTTON_6,
	ID_BUTTON_7,
	ID_BUTTON_8,
	ID_BUTTON_9,
	ID_LABEL_1
};

extern const BITMAP_INFO image1_bmp, image2_bmp, image3_bmp, image4_bmp, image5_bmp, image6_bmp, image7_bmp, image8_bmp, image9_bmp;

class c_scroll_view_v : public c_scroll_view
{
	virtual void on_init_children()
	{
		((c_button*)get_wnd_ptr(ID_BUTTON_1))->set_on_click((WND_CALLBACK)&c_scroll_view_v::on_button_clicked);
		((c_button*)get_wnd_ptr(ID_BUTTON_2))->set_on_click((WND_CALLBACK)&c_scroll_view_v::on_button_clicked);
		((c_button*)get_wnd_ptr(ID_BUTTON_3))->set_on_click((WND_CALLBACK)&c_scroll_view_v::on_button_clicked);
		((c_button*)get_wnd_ptr(ID_BUTTON_4))->set_on_click((WND_CALLBACK)&c_scroll_view_v::on_button_clicked);
		((c_button*)get_wnd_ptr(ID_BUTTON_5))->set_on_click((WND_CALLBACK)&c_scroll_view_v::on_button_clicked);
		((c_button*)get_wnd_ptr(ID_BUTTON_6))->set_on_click((WND_CALLBACK)&c_scroll_view_v::on_button_clicked);
		((c_button*)get_wnd_ptr(ID_BUTTON_7))->set_on_click((WND_CALLBACK)&c_scroll_view_v::on_button_clicked);
		((c_button*)get_wnd_ptr(ID_BUTTON_8))->set_on_click((WND_CALLBACK)&c_scroll_view_v::on_button_clicked);
		((c_button*)get_wnd_ptr(ID_BUTTON_9))->set_on_click((WND_CALLBACK)&c_scroll_view_v::on_button_clicked);

		c_scroll_view::on_init_children();
	}
	void on_button_clicked(int ctrl_id, int param)
	{
		switch (ctrl_id)
		{
		case ID_BUTTON_1:
			c_bitmap::draw_bitmap(m_surface, m_z_order, &image1_bmp, 230, 10);
			break;
		case ID_BUTTON_2:
			c_bitmap::draw_bitmap(m_surface, m_z_order, &image2_bmp, 230, 10);
			break;
		case ID_BUTTON_3:
			c_bitmap::draw_bitmap(m_surface, m_z_order, &image3_bmp, 230, 10);
			break;
		case ID_BUTTON_4:
			c_bitmap::draw_bitmap(m_surface, m_z_order, &image4_bmp, 410, 10);
			break;
		case ID_BUTTON_5:
			c_bitmap::draw_bitmap(m_surface, m_z_order, &image5_bmp, 230, 150);
			break;
		case ID_BUTTON_6:
			c_bitmap::draw_bitmap(m_surface, m_z_order, &image6_bmp, 410, 150);
			break;
		case ID_BUTTON_7:
			c_bitmap::draw_bitmap(m_surface, m_z_order, &image7_bmp, 230, 290);
			break;
		case ID_BUTTON_8:
			c_bitmap::draw_bitmap(m_surface, m_z_order, &image8_bmp, 230, 290);
			break;
		case ID_BUTTON_9:
			c_bitmap::draw_bitmap(m_surface, m_z_order, &image9_bmp, 230, 290);
			break;
		default:
			ASSERT(false);
			break;
		}
	}
};

// Layout Widgets
static c_wnd s_my_ui;
static c_scroll_view_v s_scroll_view_1;
static c_scroll_view s_scroll_view_2;
static c_button s_button_1, s_button_2, s_button_3, s_button_4, s_button_5, s_button_6, s_button_7, s_button_8, s_button_9;
static c_label label_1;

WND_TREE s_scroll_widgets_1[] =
{
	{ &s_button_1,	ID_BUTTON_1,	"Button 1",	0, 0,  220, 50},
	{ &s_button_2,	ID_BUTTON_2,	"Button 2",	0, 60, 220, 50},
	{ &s_button_3,	ID_BUTTON_3,	"Button 3",	0, 120, 220, 50},
	{ &s_button_4,	ID_BUTTON_4,	"Button 4",	0, 180, 220, 50},
	{ &s_button_5,	ID_BUTTON_5,	"Button 5",	0, 240, 220, 50},
	{ &s_button_6,	ID_BUTTON_6,	"Button 6",	0, 300, 220, 50},
	{ &s_button_7,	ID_BUTTON_7,	"Button 7",	0, 360, 220, 50},
	{ &s_button_8,	ID_BUTTON_8,	"Button 8",	0, 420, 220, 50},
	{ &s_button_9,	ID_BUTTON_9,	"Button 9",	0, 480, 220, 50},

	{NULL, 0 , 0, 0, 0, 0, 0}
};

WND_TREE s_scroll_widgets_2[] =
{
	{ &label_1, ID_LABEL_1, " You never fight alone; God bless Wuhan, God bless everyone of us!", 0, 0, 800, 100 },

	{NULL, 0 , 0, 0, 0, 0, 0}
};

WND_TREE s_main_widgets[] =
{
	{(c_wnd*)&s_scroll_view_1, ID_SCROLL_VIEW_1, 0, 0,	0,		600, 290, s_scroll_widgets_1},
	{(c_wnd*)&s_scroll_view_2, ID_SCROLL_VIEW_2, 0, 0,	300,	600, 100, s_scroll_widgets_2},
	{NULL, 0 , 0, 0, 0, 0, 0}
};

// Create GUI
extern const LATTICE_FONT_INFO Consolas_24B;
void load_resource()
{
	c_theme::add_font(FONT_DEFAULT, &Consolas_24B);
	//for button
	c_theme::add_color(COLOR_WND_FONT, GL_RGB(0, 0, 0));
	c_theme::add_color(COLOR_WND_NORMAL, GL_RGB(220, 220, 220));
	c_theme::add_color(COLOR_WND_FOCUS, GL_RGB(180, 180, 180));
}

void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes) {
	load_resource();

	c_surface* s_surface = new c_surface(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_0);
	s_display = new c_display(phy_fb, screen_width, screen_height, s_surface);

	s_surface->fill_rect(0, 0, UI_WIDTH - 1, UI_HEIGHT - 1, GL_RGB(255, 255, 255), Z_ORDER_LEVEL_0);

	s_my_ui.set_surface(s_surface);
	s_my_ui.connect(NULL, ID_ROOT, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_main_widgets);
	s_my_ui.show_window();

	while(1)
	{
		thread_sleep(10000);
	}
}

//////////////////////// interface for all platform ////////////////////////
void startHelloScroll(void* phy_fb, int width, int height, int color_bytes) {
	create_ui(phy_fb, width, height, color_bytes);
}

void sendTouch2HelloScroll(int x, int y, bool is_down)
{
	is_down ? s_my_ui.on_touch(x, y, TOUCH_DOWN) : s_my_ui.on_touch(x, y, TOUCH_UP);
}

void sendKey2HelloScroll(unsigned int key)
{
	s_my_ui.on_navigate(NAVIGATION_KEY(key));
}

void* getUiOfHelloScroll(int* width, int* height, bool force_update)
{
	return s_display->get_updated_fb(width, height, force_update);
}

int captureUiOfHelloScroll()
{
	return s_display->snap_shot("snap_short.bmp");
}
