#define GUILITE_ON  //Do not define this macro once more!!!
#include "GuiLite.h"
#include <string.h>
#include <wchar.h>
#include "freetype.h"

#define UI_WIDTH 	800
#define UI_HEIGHT 	600
#define TTF_FILE_PATH "../simhei.ttf"

static c_display* s_display;
static c_surface* s_surface;
static c_freetype s_freetype;
static FT_Face font_face;

static int s_language_index;
static const wchar_t* welcome[] = {
	L"Hello, GuiLite has only 4000+ lines of basic C++ code.\n    But, we have developers all over the world.",
	L"GuiLite僅僅只有4千行的基礎C++代碼。\n  但我們的開發者，遍佈全球。",
	L"こんにちは、GuiLiteには4000行以上のC ++コードしかありません\n  しかし、世界中に開発者がいます"
};

void show_text(const wchar_t* s)
{
	int x = 80;
	int y = 100;
	s_surface->fill_rect(0, 60, UI_WIDTH, 140, 0, Z_ORDER_LEVEL_0);

	int x_ = x;
	int y_ = y;
	while (*s)
	{
		if(*s == L'\n')
		{
			y += (font_face->size->metrics.height / 64);
			x_ = x;
			s++;
			continue;
		}
		x_ += s_freetype.draw_single_char(s_surface, Z_ORDER_LEVEL_0, *s++, x_, y, font_face, GL_RGB(172, 226, 9), 0);
		thread_sleep(50);
	}
}

void show_image()
{
	c_bitmap::draw_bitmap(s_surface, Z_ORDER_LEVEL_0, c_theme::get_bmp(BITMAP_CUSTOM1), 0, 200);
}

//////////////////////// start UI ////////////////////////
extern const BITMAP_INFO guilite_map_bmp;

void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes)
{
	//load resource
	font_face = s_freetype.set_font(TTF_FILE_PATH, 32, 32);
	c_theme::add_bitmap(BITMAP_CUSTOM1, &guilite_map_bmp);

	s_surface = new c_surface(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_0);
	s_display = new c_display(phy_fb, screen_width, screen_height, s_surface);

	show_text(welcome[s_language_index]);
	show_image();
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
	if(!is_down)
	{
		show_text(welcome[++s_language_index % (sizeof(welcome) / sizeof(wchar_t*))]);
	}
}

void* getUiOfHelloFreetype(int* width, int* height, bool force_update)
{
	return s_display ? s_display->get_updated_fb(width, height, force_update) : 0;
}

int captureUiOfHelloFreetype()
{
	return s_display ? s_display->snap_shot("snap_short.bmp") : 0;
}