#define GUILITE_ON  //Do not define this macro once more!!!
#include "GuiLite.h"
#include <math.h>

#define UI_WIDTH 240
#define UI_HEIGHT 320
#define SQUARE_SIZE_1 10
#define SQUARE_SIZE_2 14
#define PI 3.14159

static c_surface* s_surface;
static c_display* s_display;
static int s_mode;

namespace pendulum
{
	int r1 = 90;
	int r2 = 90;
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	float m1 = 25;
	float m2 = 50;
	float a1 = PI / 2;
	float a2 = PI / 2;
	float a1_v = 0;
	float a2_v = 0;
	float g = 0.5;

	void draw(int x, int y, const char* text1 = 0, const char* text2 = 0)
	{
		//caculate acceleration
		float num1 = -g * (2 * m1 + m2) * sin(a1);
		float num2 = -m2 * g * sin(a1 - 2 * a2);
		float num3 = -2 * sin(a1 - a2) * m2;
		float num4 = a2_v * a2_v * r2 + a1_v * a1_v * r1 * cos(a1 - a2);
		float den = r1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
		float a1_a = (num1 + num2 + num3 * num4) / den;

		num1 = 2 * sin(a1 - a2);
		num2 = (a1_v * a1_v * r1 * (m1 + m2));
		num3 = g * (m1 + m2) * cos(a1);
		num4 = a2_v * a2_v * r2 * m2 * cos(a1 - a2);
		den = r2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
		float a2_a = (num1 * (num2 + num3 + num4)) / den;

		a1_v += a1_a;
		a2_v += a2_a;
		a1 += a1_v;
		a2 += a2_v;
		//earse footprint
		s_surface->draw_line(x, y, x1 + x, y1 + y, 0, Z_ORDER_LEVEL_0);
		s_surface->draw_line(x1 + x, y1 + y, x2 + x, y2 + y, 0, Z_ORDER_LEVEL_0);

		if (text1 && text2)
		{
			c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, text1, x1 + x - 14, y1 + y - 10, c_theme::get_font(FONT_DEFAULT), 0, 0, ALIGN_HCENTER);
			c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, text2, x2 + x - 18, y2 + y - 10, c_theme::get_font(FONT_DEFAULT), 0, 0, ALIGN_HCENTER);
		}
		else
		{
			s_surface->draw_rect(c_rect(x1 + x - SQUARE_SIZE_1 / 2, y1 + y - SQUARE_SIZE_1 / 2, SQUARE_SIZE_1, SQUARE_SIZE_1), 0, 1, Z_ORDER_LEVEL_0);
			s_surface->draw_rect(c_rect(x2 + x - SQUARE_SIZE_2 / 2, y2 + y - SQUARE_SIZE_2 / 2, SQUARE_SIZE_2, SQUARE_SIZE_2), 0, 1, Z_ORDER_LEVEL_0);
		}
		//draw new picture
		x1 = r1 * sin(a1);
		y1 = r1 * cos(a1);
		x2 = r2 * sin(a2) + x1;
		y2 = r2 * cos(a2) + y1;

		s_surface->draw_line(x, y, x1 + x, y1 + y, GL_RGB(0, 162, 232), Z_ORDER_LEVEL_0);
		s_surface->draw_line(x1 + x, y1 + y, x2 + x, y2 + y, GL_RGB(0, 162, 232), Z_ORDER_LEVEL_0);

		if (text1 && text2)
		{
			c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, text1, x1 + x - 14, y1 + y - 10, c_theme::get_font(FONT_DEFAULT), GL_RGB(255, 255, 255), 0, ALIGN_HCENTER);
			c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, text2, x2 + x - 18, y2 + y - 10, c_theme::get_font(FONT_DEFAULT), GL_RGB(255, 255, 255), 0, ALIGN_HCENTER);
		}
		else
		{
			s_surface->draw_rect(c_rect(x1 + x - SQUARE_SIZE_1 / 2, y1 + y - SQUARE_SIZE_1 / 2, SQUARE_SIZE_1, SQUARE_SIZE_1), GL_RGB(255, 255, 255), 1, Z_ORDER_LEVEL_0);
			s_surface->draw_rect(c_rect(x2 + x - SQUARE_SIZE_2 / 2, y2 + y - SQUARE_SIZE_2 / 2, SQUARE_SIZE_2, SQUARE_SIZE_2), GL_RGB(255, 255, 255), 1, Z_ORDER_LEVEL_0);
		}
	}
}

extern const FONT_INFO Consolas_19;
void load_resource()
{
	c_theme::add_font(FONT_DEFAULT, &Consolas_19);
}

//////////////////////// start UI ////////////////////////
void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op) {
	if (phy_fb)
	{
		static c_surface surface(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_0);
		static c_display display(phy_fb, screen_width, screen_height, &surface);
		s_surface = &surface;
		s_display = &display;
	}
	else
	{//for MCU without framebuffer
		static c_surface_no_fb surface_no_fb(UI_WIDTH, UI_HEIGHT, color_bytes, gfx_op, Z_ORDER_LEVEL_0);
		static c_display display(phy_fb, screen_width, screen_height, &surface_no_fb);
		s_surface = &surface_no_fb;
		s_display = &display;
	}
	load_resource();
	s_surface->fill_rect(c_rect(0, 0, UI_WIDTH, UI_HEIGHT), 0, Z_ORDER_LEVEL_0);

	while (true)
	{
		s_mode ? pendulum::draw(120, 100, "Gui", "Lite") : pendulum::draw(120, 100);
		thread_sleep(30);
	}
}

//////////////////////// interface for all platform ////////////////////////
extern "C" void startHelloPendulum(void* phy_fb, int width, int height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op) {
	create_ui(phy_fb, width, height, color_bytes, gfx_op);
}

extern "C" void sendKey2HelloPendulum(unsigned int key)
{
	s_surface->fill_rect(c_rect(0, 0, UI_WIDTH, UI_HEIGHT), 0, Z_ORDER_LEVEL_0);
	s_mode = s_mode ? 0 : 1;
}

void* getUiOfHelloPendulum(int* width, int* height, bool force_update)
{
	if (s_display)
	{
		return s_display->get_updated_fb(width, height, force_update);
	}
	return NULL;
}
