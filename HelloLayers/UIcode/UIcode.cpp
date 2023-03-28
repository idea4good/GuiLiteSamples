#define GUILITE_ON  //Do not define this macro once more!!!
#include "GuiLite.h"

#define UI_WIDTH 240
#define UI_HEIGHT 320

#define LAYER_1_X 70
#define LAYER_1_Y 100

#define SHADES_CNT 10
#define SHADE_HEIGHT 10
#define LAYER_1_WIDTH  80
#define LAYER_1_HEIGHT SHADES_CNT * SHADE_HEIGHT

static c_surface* s_surface;
static c_display* s_display;
c_rect overlapped_rect(LAYER_1_X, LAYER_1_Y, LAYER_1_WIDTH, LAYER_1_HEIGHT);
//////////////////////// start UI ////////////////////////

void draw_on_layer_0()
{
	int const start_y = 70;
	s_surface->fill_rect(c_rect(0, 0, UI_WIDTH, UI_HEIGHT), 0, Z_ORDER_LEVEL_0);
	c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "We could not to do", 30, start_y + 30, c_theme::get_font(FONT_DEFAULT), GL_RGB(255, 255, 255), GL_ARGB(0, 0, 0, 0));
	c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "everything for you.", 30, start_y + 50, c_theme::get_font(FONT_DEFAULT), GL_RGB(255, 255, 255), GL_ARGB(0, 0, 0, 0));
	c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "", 30, start_y + 50, c_theme::get_font(FONT_DEFAULT), GL_RGB(255, 255, 255), GL_ARGB(0, 0, 0, 0));

	c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "Just keep GUI:", 30, start_y + 90, c_theme::get_font(FONT_DEFAULT), GL_RGB(255, 255, 255), GL_ARGB(0, 0, 0, 0));
	c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "stupid simple.", 30, start_y + 110, c_theme::get_font(FONT_DEFAULT), GL_RGB(255, 255, 255), GL_ARGB(0, 0, 0, 0));
}

void draw_on_layer_1()
{
	//activate the layer 1.
	s_surface->activate_layer(overlapped_rect, Z_ORDER_LEVEL_1);
	//draw everything inside the active rect.
	s_surface->fill_rect(c_rect(LAYER_1_X, LAYER_1_Y, LAYER_1_WIDTH, LAYER_1_HEIGHT), GL_RGB(0, 122, 204), Z_ORDER_LEVEL_1);
	c_word::draw_string(s_surface, Z_ORDER_LEVEL_1, "GuiLite", LAYER_1_X + 5, LAYER_1_Y + 20, c_theme::get_font(FONT_DEFAULT), GL_RGB(255, 255, 255), GL_RGB(0, 122, 204));
	c_word::draw_string(s_surface, Z_ORDER_LEVEL_1, "4 KLOC", LAYER_1_X + 5, LAYER_1_Y + 60, c_theme::get_font(FONT_DEFAULT), GL_RGB(255, 255, 255), GL_RGB(0, 122, 204));
}

void clear_layer_1()
{
	s_surface->activate_layer(c_rect(), Z_ORDER_LEVEL_1);//inactivate the layer 1 by empty rect, and show the layers below.
}

extern const LATTICE_FONT_INFO Consolas_19;
void load_resource()
{
	c_theme::add_font(FONT_DEFAULT, &Consolas_19);
}

void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes, struct DISPLAY_DRIVER* driver) {
	static c_surface surface(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_1, overlapped_rect);
	static c_display display(phy_fb, screen_width, screen_height, &surface, driver);
	s_surface = &surface;
	s_display = &display;

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
extern "C" void startHelloLayers(void* phy_fb, int width, int height, int color_bytes, struct DISPLAY_DRIVER* driver) {
	create_ui(phy_fb, width, height, color_bytes, driver);
}

void* getUiOfHelloLayers(int* width, int* height, bool force_update)
{
	if (s_display)
	{
		return s_display->get_updated_fb(width, height, force_update);
	}
	return NULL;
}
