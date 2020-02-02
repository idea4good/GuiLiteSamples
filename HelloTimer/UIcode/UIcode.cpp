#define GUILITE_ON  //Do not define this macro once more!!!
#include "GuiLite.h"
#include <math.h>

const int UI_WIDTH = 240;
const int UI_HEIGHT = 320;
const int FRAME_COUNT = 32;

extern const FONT_INFO _DengXian_36B;
extern const BITMAP_INFO humidity_bmp;
extern const BITMAP_INFO temperature_bmp;
extern const BITMAP_INFO weather_bmp;
extern const BITMAP_INFO grass_bmp;

static c_surface* s_surface;

class c_hand
{
public:
	void set(int x, int y, float start_len, float end_len, float start_angle, float end_angle, unsigned int rgb)
	{
		m_pos_x = x;
		m_pos_y = y;
		m_rgb = rgb;
		m_start_len = start_len;
		m_end_len = end_len;
		m_start_angle = start_angle;
		m_end_angle = end_angle;

		m_len_step = ((m_end_len - m_start_len) / FRAME_COUNT);
		m_angle_step = ((m_end_angle - m_start_angle) / FRAME_COUNT);
	}
	bool show()
	{
		if (fabs(m_start_len - m_end_len) < 1.0)
		{
			return true;
		}
		//erase footprint
		int x = (m_start_len) * cos(m_start_angle) + m_pos_x;
		int y = (m_start_len) * sin(m_start_angle) + m_pos_y;
		s_surface->draw_line(m_pos_x, m_pos_y, x, y, 0, Z_ORDER_LEVEL_0);

		m_start_len += m_len_step;
		m_start_angle += m_angle_step;

		x = (m_start_len) * cos(m_start_angle) + m_pos_x;
		y = (m_start_len) * sin(m_start_angle) + m_pos_y;
		s_surface->draw_line(m_pos_x, m_pos_y, x, y, m_rgb, Z_ORDER_LEVEL_0);
			
		return false;
	}
private:
	int m_pos_x, m_pos_y;
	unsigned int m_rgb;
	
	float m_start_len;
	float m_end_len;
	float m_len_step;
	
	float m_start_angle;
	float m_end_angle;
	float m_angle_step;
};

class c_clock
{
public:
	c_clock() : m_x(120), m_y(120), pi(3.1415926535 / 180) {}
	void set_hands(float start_radius, float end_radius, float hour_start_len, float hour_end_len, float hour_start_angle, float hour_end_angle, unsigned int hour_rgb, float minute_start_len, float minute_end_len, float minute_start_angle, float minute_end_angle, unsigned int minute_rgb, float second_start_len, float second_end_len, float second_start_angle, float second_end_angle, unsigned int second_rgb)
	{
		m_hour.set(m_x, m_y, hour_start_len, hour_end_len, hour_start_angle, hour_end_angle, hour_rgb);
		m_minute.set(m_x, m_y, minute_start_len, minute_end_len, minute_start_angle, minute_end_angle, minute_rgb);
		m_second.set(m_x, m_y, second_start_len, second_end_len, second_start_angle, second_end_angle, second_rgb);
		m_start_radius = start_radius;
		m_end_radius = end_radius;
		m_step = ((m_end_radius - m_start_radius) / FRAME_COUNT);
	}
	bool drawSacle()
	{
		if (fabs(m_start_radius - m_end_radius) < 1.0)
		{
			return true;
		}

		drawCircle(m_start_radius, 0);
		m_start_radius += m_step;
		drawCircle(m_start_radius, GL_RGB(0, 175, 235));
		return false;
	}
	void show()
	{
		bool complete = false;
		while (!complete)
		{
			complete = drawSacle();
			complete &= m_hour.show();
			complete &= m_minute.show();
			complete &= m_second.show();
			thread_sleep(20);
		}
	}
	void drawCircle(int r, unsigned int rgb)
	{
		int tmpX, tmpY, lastX, lastY;
		lastX = lastY = 0;

		for (float angle = 0.5; angle < 90; angle += 0.5)//Bigger circle, Smaller angle step
		{
			tmpX = r * cos(angle * pi);
			tmpY = r * sin(angle * pi);
			if (tmpX == lastX && tmpY == lastY)
			{
				continue;
			}
			
			s_surface->draw_pixel(m_x + tmpX, m_y + tmpY, rgb, Z_ORDER_LEVEL_0);
			s_surface->draw_pixel(m_x - tmpX, m_y + tmpY, rgb, Z_ORDER_LEVEL_0);
			s_surface->draw_pixel(m_x + tmpX, m_y - tmpY, rgb, Z_ORDER_LEVEL_0);
			s_surface->draw_pixel(m_x - tmpX, m_y - tmpY, rgb, Z_ORDER_LEVEL_0);
		}
	}
private:
	int m_x;
	int m_y;
	float m_start_radius;
	float m_end_radius;
	float m_step;

	c_hand m_hour;
	c_hand m_minute;
	c_hand m_second;
	const float pi;
};

class c_weather
{
public:
	c_weather() : m_weather_x(16), m_weather_y(96), m_temperature_x(129), m_temperature_y(73), m_humidity_x(126), m_humidity_y(144), m_temp_value_x(174), m_temp_value_y(88), m_humidity_value_x(174), m_humidity_value_y(159), m_day_x(0), m_day_y(25), m_distance(60), m_frame_count(6) {}
	void show()
	{
		int step = m_distance / m_frame_count;
		int distance = m_distance;
		while (distance > 0)
		{
			//erase footprint
			c_word::draw_string_in_rect(s_surface, Z_ORDER_LEVEL_0, "Today", c_rect(m_day_x, m_day_y - distance, 240, 48), c_theme::get_font(FONT_DEFAULT), 0, 0, ALIGN_HCENTER);

			s_surface->fill_rect(m_weather_x - distance, m_weather_y, m_weather_x - distance + step, m_weather_y + weather_bmp.height, 0, Z_ORDER_LEVEL_0);

			s_surface->fill_rect(m_temperature_x + distance + temperature_bmp.width - step, m_temperature_y, m_temperature_x + distance +  temperature_bmp.width, m_temperature_y + temperature_bmp.height, 0, Z_ORDER_LEVEL_0);
			c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "25C", m_temp_value_x + distance, m_temp_value_y, c_theme::get_font(FONT_DEFAULT), 0, 0);

			s_surface->fill_rect(m_humidity_x + distance + humidity_bmp.width - step, m_humidity_y, m_humidity_x + distance + humidity_bmp.width, m_humidity_y + humidity_bmp.height, 0, Z_ORDER_LEVEL_0);
			c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "75%", m_humidity_value_x + distance, m_humidity_value_y, c_theme::get_font(FONT_DEFAULT), 0, 0);

			distance -= step;

			//show at new position
			c_word::draw_string_in_rect(s_surface, Z_ORDER_LEVEL_0, "Today", c_rect(m_day_x, m_day_y - distance, 240, 48), c_theme::get_font(FONT_DEFAULT), GL_RGB(0, 163, 233), 0, ALIGN_HCENTER);

			c_bitmap::draw_bitmap(s_surface, Z_ORDER_LEVEL_0, &weather_bmp, m_weather_x - distance, m_weather_y);

			c_bitmap::draw_bitmap(s_surface, Z_ORDER_LEVEL_0, &temperature_bmp, m_temperature_x + distance, m_temperature_y);
			c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "25C", m_temp_value_x + distance, m_temp_value_y, c_theme::get_font(FONT_DEFAULT), GL_RGB(0, 163, 233), 0);

			s_surface->draw_hline(156, 240, 132, GL_RGB(0, 163, 233), Z_ORDER_LEVEL_0);

			c_bitmap::draw_bitmap(s_surface, Z_ORDER_LEVEL_0, &humidity_bmp, m_humidity_x + distance, m_humidity_y);
			c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "75%", m_humidity_value_x + distance, m_humidity_value_y, c_theme::get_font(FONT_DEFAULT), GL_RGB(0, 163, 233), 0);

			thread_sleep(20);
		}
	}

	void disappear()
	{
		int step = m_distance / m_frame_count;
		int distance = 0;
		while (distance < m_distance)
		{
			//erase footprint
			c_word::draw_string_in_rect(s_surface, Z_ORDER_LEVEL_0, "Today", c_rect(m_day_x, m_day_y - distance, 240, 48), c_theme::get_font(FONT_DEFAULT), 0, 0, ALIGN_HCENTER);

			s_surface->fill_rect(m_weather_x - distance + weather_bmp.width, m_weather_y, m_weather_x - distance + weather_bmp.width + step, m_weather_y + weather_bmp.height, 0, Z_ORDER_LEVEL_0);

			s_surface->fill_rect(m_temperature_x + distance - step, m_temperature_y, m_temperature_x + distance, m_temperature_y + temperature_bmp.height, 0, Z_ORDER_LEVEL_0);
			c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "25C", m_temp_value_x + distance, m_temp_value_y, c_theme::get_font(FONT_DEFAULT), 0, 0);

			s_surface->fill_rect(m_humidity_x + distance - step, m_humidity_y, m_humidity_x + distance, m_humidity_y + humidity_bmp.height, 0, Z_ORDER_LEVEL_0);
			c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "75%", m_humidity_value_x + distance, m_humidity_value_y, c_theme::get_font(FONT_DEFAULT), 0, 0);
			
			distance += step;

			//show at new position
			c_word::draw_string_in_rect(s_surface, Z_ORDER_LEVEL_0, "Today", c_rect(m_day_x, m_day_y - distance, 240, 48), c_theme::get_font(FONT_DEFAULT), GL_RGB(0, 163, 233), 0, ALIGN_HCENTER);

			c_bitmap::draw_bitmap(s_surface, Z_ORDER_LEVEL_0, &weather_bmp, m_weather_x - distance, m_weather_y);

			c_bitmap::draw_bitmap(s_surface, Z_ORDER_LEVEL_0, &temperature_bmp, m_temperature_x + distance, m_temperature_y);
			c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "25C", m_temp_value_x + distance, m_temp_value_y, c_theme::get_font(FONT_DEFAULT), GL_RGB(0, 163, 233), 0);

			s_surface->draw_hline(156, 240, 132, GL_RGB(0, 163, 233), Z_ORDER_LEVEL_0);

			c_bitmap::draw_bitmap(s_surface, Z_ORDER_LEVEL_0, &humidity_bmp, m_humidity_x + distance, m_humidity_y);
			c_word::draw_string(s_surface, Z_ORDER_LEVEL_0, "75%", m_humidity_value_x + distance, m_humidity_value_y, c_theme::get_font(FONT_DEFAULT), GL_RGB(0, 163, 233), 0);

			thread_sleep(20);
		}
	}
private:
	int m_weather_x, m_weather_y;
	int m_temperature_x, m_temperature_y;
	int m_humidity_x, m_humidity_y;
	int m_temp_value_x, m_temp_value_y;
	int m_humidity_value_x, m_humidity_value_y;
	int m_day_x, m_day_y;
	int m_distance, m_frame_count;
};

void load_resource()
{
	c_theme::add_font(FONT_DEFAULT, &_DengXian_36B);
}

void switchUI()
{
	static int index = 0;
	c_weather weather;
	c_clock timer;

	switch (index++ % 4)
	{
	case 0:
		weather.show();
		return;
	case 1:
		weather.disappear();
		s_surface->fill_rect(0, 0, UI_WIDTH, 240, 0, Z_ORDER_LEVEL_0);
		return;
	case 2:
		s_surface->fill_rect(0, 0, UI_WIDTH, 240, 0, Z_ORDER_LEVEL_0);
		timer.set_hands(140.0, 100.0, 0.0, 40.0, 0.0, 2.0, GL_RGB(255, 255, 255), 0.0, 70.0, 0.0, 4.0, GL_RGB(255, 255, 255), 0.0, 90.0, 0.0, 6.0, GL_RGB(237, 125, 124));
		timer.show();
		return;
	case 3:
		timer.set_hands(100.0, 140.0, 40.0, 0.0, 2.0, 0.0, GL_RGB(255, 255, 255), 70.0, 0.0, 4.0, 0.0, GL_RGB(255, 255, 255), 90.0, 0.0, 6.0, 0.0, GL_RGB(237, 125, 124));
		timer.show();
		s_surface->fill_rect(0, 0, UI_WIDTH, 270, 0, Z_ORDER_LEVEL_0);
		break;
	default:
		return;
	}
}

void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op)
{
	load_resource();

	static c_display display(phy_fb, screen_width, screen_height, UI_WIDTH, UI_HEIGHT, color_bytes, 1, gfx_op);
	s_surface = display.alloc_surface(Z_ORDER_LEVEL_0);
	s_surface->set_active(true);

	//background
	s_surface->fill_rect(0, 0, UI_WIDTH, UI_HEIGHT, 0, Z_ORDER_LEVEL_0);
	c_bitmap::draw_bitmap(s_surface, Z_ORDER_LEVEL_0, &grass_bmp, 0, 271);

	while(1)
	{
		switchUI();
		thread_sleep(1000);
	}
}

//////////////////////// interface for all platform ////////////////////////
extern "C" void startHelloTimer(void* phy_fb, int width, int height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op)
{
	create_ui(phy_fb, width, height, color_bytes, gfx_op);
}
