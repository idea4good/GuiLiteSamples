#define GUILITE_ON  //Do not define this macro once more!!!
#include "GuiLite.h"
#include <string.h>
#include <wchar.h>
#include "freetype_operator.h"

#define UI_WIDTH 	800
#define UI_HEIGHT 	600
#define TTF_FILE_PATH "../simhei.ttf"

static c_display* s_display;
static c_freetype_font_op the_freetype_font_op;
static const wchar_t* welcome[] = {
	L"Hello, GuiLite has only 4000+ lines of basic C++ code.\n    But, we have developers all over the world.",
	L"GuiLite僅僅只有4千行的基礎C++代碼。\n  但我們的開發者，遍佈全球。",
	L"こんにちは、GuiLiteには4000行以上のC ++コードしかありません\n  しかし、世界中に開発者がいます"
};

//////////////////////// define widgets & map message ////////////////////////
enum WND_ID
{
	ID_DESKTOP = 1,
	ID_BUTTON
};

class c_myUI : public c_wnd
{
	virtual void on_init_children()
	{
		c_button* button = (c_button*)get_wnd_ptr(ID_BUTTON);
		button->set_on_click((WND_CALLBACK)&c_myUI::on_clicked);
	}

	virtual void on_paint(void)
	{
		c_bitmap::draw_bitmap(m_surface, m_z_order, c_theme::get_bmp(BITMAP_CUSTOM1), 0, 200);
		on_clicked(ID_BUTTON, 0);
	}

	void on_clicked(int ctrl_id, int param)
	{
		m_surface->fill_rect(0, 60, UI_WIDTH, 140, 0, Z_ORDER_LEVEL_0);
		c_word::draw_string(m_surface, Z_ORDER_LEVEL_0, welcome[s_language_index++ % (sizeof(welcome) / sizeof(wchar_t*))], 80, 50, c_theme::get_font(FONT_DEFAULT), GL_RGB(172, 226, 9), 0);
	}
	int s_language_index = 0;
};

//////////////////////// layout UI ////////////////////////
static c_myUI s_myUI;
static c_button	s_button;

static WND_TREE s_myUI_children[] =
{
	{(c_wnd*)&s_button, ID_BUTTON, (const char*)L"NEXT", 330, 540, 100, 50, NULL},
	{ NULL,0,0,0,0,0,0 }
};

//////////////////////// start UI ////////////////////////
extern const BITMAP_INFO guilite_map_bmp;
void load_resource()
{
	c_word::fontOperator = &the_freetype_font_op;
	c_theme::add_font(FONT_DEFAULT, the_freetype_font_op.set_font(TTF_FILE_PATH, 32, 32));
	c_theme::add_bitmap(BITMAP_CUSTOM1, &guilite_map_bmp);
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
	while(1)
	{
		thread_sleep(1000000);
	}
}

//////////////////////// interface for all platform ////////////////////////
void startHelloFreetype(void* phy_fb, int width, int height, int color_bytes)
{
	create_ui(phy_fb, width, height, color_bytes);
}

void sendTouch2HelloFreetype(int x, int y, bool is_down)
{
	is_down ? s_myUI.on_touch(x, y, TOUCH_DOWN) : s_myUI.on_touch(x, y, TOUCH_UP);
}

void* getUiOfHelloFreetype(int* width, int* height, bool force_update)
{
	return s_display ? s_display->get_updated_fb(width, height, force_update) : 0;
}

int captureUiOfHelloFreetype()
{
	return s_display ? s_display->snap_shot("snap_short.bmp") : 0;
}