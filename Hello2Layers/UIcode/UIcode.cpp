#define GUILITE_ON  //Do not define this macro once more!!!
#include "GuiLite.h"
#include <stdlib.h>

#define UI_WIDTH 240
#define UI_HEIGHT 320

#define LAYER_2_X 70
#define LAYER_2_Y 110
#define LAYER_2_WIDTH  100
#define LAYER_2_HEIGHT 100

static c_surface* s_surface;
static c_display* s_display;
//////////////////////// start UI ////////////////////////

void draw_layer_1()
{
	s_surface->fill_rect(0, 0, UI_WIDTH - 1, UI_HEIGHT - 1, 0, Z_ORDER_LEVEL_0);
}

void draw_layer_2()
{
	s_surface->fill_rect(LAYER_2_X, LAYER_2_Y, LAYER_2_X + LAYER_2_WIDTH - 1, LAYER_2_Y + LAYER_2_HEIGHT - 1, GL_RGB(255, 0, 0), Z_ORDER_LEVEL_1);
}

void clear_layer_2()
{
	c_rect overlapped_rect(LAYER_2_X, LAYER_2_Y, LAYER_2_X + LAYER_2_WIDTH - 1, LAYER_2_Y + LAYER_2_HEIGHT - 1);
	s_surface->show_overlapped_rect(overlapped_rect, Z_ORDER_LEVEL_0);
}

void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op) {
	if (phy_fb)
	{
		static c_surface surface(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_1, c_rect(LAYER_2_X, LAYER_2_Y, LAYER_2_X + LAYER_2_WIDTH - 1, LAYER_2_Y + LAYER_2_HEIGHT - 1));
		static c_display display(phy_fb, screen_width, screen_height, &surface);
		s_surface = &surface;
		s_display = &display;
	}
	else
	{//for MCU without framebuffer
		static c_surface_no_fb surface_no_fb(UI_WIDTH, UI_HEIGHT, color_bytes, gfx_op, Z_ORDER_LEVEL_1, c_rect(LAYER_2_X, LAYER_2_Y, LAYER_2_X + LAYER_2_WIDTH - 1, LAYER_2_Y + LAYER_2_HEIGHT - 1));
		static c_display display(phy_fb, screen_width, screen_height, &surface_no_fb);
		s_surface = &surface_no_fb;
		s_display = &display;
	}

	draw_layer_1();
	while(1) {
		draw_layer_2();
		thread_sleep(2000);
		clear_layer_2();
		thread_sleep(2000);
	}
}

//////////////////////// interface for all platform ////////////////////////
extern "C" void startHello2Layers(void* phy_fb, int width, int height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op) {
	create_ui(phy_fb, width, height, color_bytes, gfx_op);
}

void* getUiOfHello2Layers(int* width, int* height, bool force_update)
{
	if (s_display)
	{
		return s_display->get_updated_fb(width, height, force_update);
	}
	return NULL;
}
