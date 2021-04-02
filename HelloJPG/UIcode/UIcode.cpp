#define GUILITE_ON  //Do not define this macro once more!!!
#include "GuiLite.h"
#include <string.h>
#include <wchar.h>
#include "jpg_operator.h"

#define UI_WIDTH 	800
#define UI_HEIGHT 	600

static c_display* s_display;
static c_surface* s_surface;
static c_jpg_operator the_jpg_operator;
//////////////////////// start UI ////////////////////////
void draw_image(int index)
{
	switch (index)
	{
	case 0:
		c_image::draw_image(s_surface, Z_ORDER_LEVEL_0, c_theme::get_image(IMAGE_CUSTOM1), 0, 0);
		break;
	case 1:
		c_image::draw_image(s_surface, Z_ORDER_LEVEL_0, c_theme::get_image(IMAGE_CUSTOM2), 400, 0);
		break;
	case 2:
		c_image::draw_image(s_surface, Z_ORDER_LEVEL_0, "../2.jpg", 0, 300);
		break;
	case 3:
		c_image::draw_image(s_surface, Z_ORDER_LEVEL_0, "../3.jpg", 400, 300);
		break;
	}
}

extern const BITMAP_INFO guilite_map_bmp;
void load_resource()
{
	c_image::image_operator = &the_jpg_operator;
	c_theme::add_image(IMAGE_CUSTOM1, "../0.jpg");
	c_theme::add_image(IMAGE_CUSTOM2, "../1.jpg");
}

void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes)
{
	load_resource();
	s_surface = new c_surface(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_0);
	s_display = new c_display(phy_fb, screen_width, screen_height, s_surface);

	while(1)
	{
		thread_sleep(1000000);
	}
}

//////////////////////// interface for all platform ////////////////////////
void startHelloJPG(void* phy_fb, int width, int height, int color_bytes)
{
	create_ui(phy_fb, width, height, color_bytes);
}

void sendTouch2HelloJPG(int x, int y, bool is_down)
{
	static int index;
	if (is_down)
	{
		draw_image(index++);
	}
}

void* getUiOfHelloJPG(int* width, int* height, bool force_update)
{
	return s_display ? s_display->get_updated_fb(width, height, force_update) : 0;
}

int captureUiOfHelloJPG()
{
	return s_display ? s_display->snap_shot("snap_short.bmp") : 0;
}