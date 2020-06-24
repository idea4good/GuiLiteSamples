#define GUILITE_ON  //Do not define this macro once more!!!
#include "GuiLite.h"

#define UI_WIDTH 240
#define UI_HEIGHT 320

#define LAYER_1_X 70
#define LAYER_1_Y 110

#define SHADES_CNT 10
#define SHADE_HEIGHT 10
#define LAYER_1_WIDTH  80
#define LAYER_1_HEIGHT SHADES_CNT * SHADE_HEIGHT

static c_surface* s_surface;
static c_display* s_display;

//////////////////////// start UI ////////////////////////

void draw_on_layer_0()
{
	s_surface->fill_rect(0, 0, UI_WIDTH - 1, UI_HEIGHT - 1, 0, Z_ORDER_LEVEL_0);
	c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "layer 0: the bottom", 30, LAYER_1_Y + 30, c_theme::get_font(FONT_DEFAULT), GL_RGB(255, 255, 255), GL_ARGB(0, 0, 0, 0));
}

void draw_on_layer_1()
{
	s_surface->fill_rect(LAYER_1_X, LAYER_1_Y, LAYER_1_X + LAYER_1_WIDTH - 1, LAYER_1_Y + LAYER_1_HEIGHT - 1, GL_RGB(0, 122, 204), Z_ORDER_LEVEL_1);
	c_word::draw_string(s_surface, Z_ORDER_LEVEL_1, "layer 1:", LAYER_1_X + 5, LAYER_1_Y + 19, c_theme::get_font(FONT_DEFAULT), GL_RGB(255, 255, 255), GL_RGB(0, 122, 204));
	c_word::draw_string(s_surface, Z_ORDER_LEVEL_1, "the top", LAYER_1_X + 5, LAYER_1_Y + 38, c_theme::get_font(FONT_DEFAULT), GL_RGB(255, 255, 255), GL_RGB(0, 122, 204));
}

void clear_layer_1()
{
#if 0
	//no animation
	c_rect overlapped_rect(LAYER_1_X, LAYER_1_Y, LAYER_1_X + LAYER_1_WIDTH - 1, LAYER_1_Y + LAYER_1_HEIGHT - 1);
	s_surface->show_overlapped_rect(overlapped_rect, Z_ORDER_LEVEL_0);
#else
	//animation
	for (int offset = 0; offset < SHADE_HEIGHT; offset++)
	{
		for (int i = 0; i < SHADES_CNT; i++)
		{
			c_rect overlapped_rect_top(LAYER_1_X, LAYER_1_Y + (SHADE_HEIGHT * i) + offset, LAYER_1_X + LAYER_1_WIDTH - 1, LAYER_1_Y + (SHADE_HEIGHT * i) + offset);
			s_surface->show_overlapped_rect(overlapped_rect_top, Z_ORDER_LEVEL_0);
		}
		thread_sleep(5);
	}
#endif
}

extern const FONT_INFO Consolas_19;
void load_resource()
{
	c_theme::add_font(FONT_DEFAULT, &Consolas_19);
}

void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op) {
	if (phy_fb)
	{
		static c_surface surface(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_1, c_rect(LAYER_1_X, LAYER_1_Y, LAYER_1_X + LAYER_1_WIDTH - 1, LAYER_1_Y + LAYER_1_HEIGHT - 1));
		static c_display display(phy_fb, screen_width, screen_height, &surface);
		s_surface = &surface;
		s_display = &display;
	}
	else
	{//for MCU without framebuffer
		static c_surface_no_fb surface_no_fb(UI_WIDTH, UI_HEIGHT, color_bytes, gfx_op, Z_ORDER_LEVEL_1, c_rect(LAYER_1_X, LAYER_1_Y, LAYER_1_X + LAYER_1_WIDTH - 1, LAYER_1_Y + LAYER_1_HEIGHT - 1));
		static c_display display(phy_fb, screen_width, screen_height, &surface_no_fb);
		s_surface = &surface_no_fb;
		s_display = &display;
	}

	load_resource();
	draw_on_layer_0();
	while(1) {
		draw_on_layer_1();
		thread_sleep(3000);
		clear_layer_1();
		thread_sleep(3000);
	}
}

//////////////////////// interface for all platform ////////////////////////
extern "C" void startHelloLayers(void* phy_fb, int width, int height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op) {
	create_ui(phy_fb, width, height, color_bytes, gfx_op);
}

void* getUiOfHelloLayers(int* width, int* height, bool force_update)
{
	if (s_display)
	{
		return s_display->get_updated_fb(width, height, force_update);
	}
	return NULL;
}
