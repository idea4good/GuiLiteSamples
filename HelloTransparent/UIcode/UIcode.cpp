#include <stdio.h>
#define GUILITE_ON	//Do not define this macro once more!!!
#include "GuiLite.h"
#include "surface_transparent.h"

#define UI_WIDTH	522
#define UI_HEIGHT	657

static const unsigned char	s_wave_data1[] =
{
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7E, 0x7E, 0x7F, 0x81, 0x81, 0x82, 0x82, 0x83,	0x84, 0x84, 0x84, 0x84, 0x83, 0x82, 0x82, 0x81,
	0x81, 0x7F, 0x7F, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7D, 0x7D, 0x7C, 0x7B, 0x7A, 0x79, 0x7A, 0x82,
	0x89, 0x91, 0x98, 0x9F, 0xA2, 0x9B, 0x94, 0x8C,	0x85, 0x7E, 0x78, 0x79, 0x7A, 0x7B, 0x7D, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,	0x7E, 0x7F, 0x7F, 0x81, 0x81, 0x82, 0x83, 0x84,	0x84, 0x85, 0x86, 0x87, 0x87, 0x87, 0x88, 0x88,
	0x89, 0x89, 0x89, 0x8A, 0x8A, 0x8A, 0x8A, 0x89,	0x89, 0x88, 0x88, 0x87, 0x87, 0x85, 0x85, 0x85,	0x83, 0x82, 0x81, 0x81, 0x7F, 0x7E, 0x7E, 0x7D,	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D
};

static c_surface_transparent* s_surface;
static c_display* s_display;

enum WND_ID
{
	ID_ROOT = 1,
	ID_WAVE,
	ID_DIALOG,
	ID_BUTTON
};

class c_wave : public c_wave_ctrl
{
	virtual void on_paint()
	{
		c_rect rect;
		get_screen_rect(rect);
		c_image::draw_image(s_surface, Z_ORDER_LEVEL_0, c_theme::get_image(IMAGE_CUSTOM1), rect.m_left, rect.m_top);
		save_background();
	}
	virtual void on_init_children()//should be pre_create
	{
		c_wave_ctrl::on_init_children();
		c_rect rect;
		get_screen_rect(rect);
		m_wave_top = rect.m_top + 270;
		m_wave_bottom = m_wave_top + 100;
	}
};

class c_my_dialog : public c_dialog
{
	virtual void on_init_children()
	{
		((c_button*)get_wnd_ptr(ID_BUTTON))->set_on_click((WND_CALLBACK)&c_my_dialog::on_clicked);
	}
	virtual void on_paint(void)
	{
		c_rect rect;
		get_screen_rect(rect);
		s_surface->fill_rect(rect.m_left, rect.m_top, rect.m_right, rect.m_bottom, GL_ARGB(220, 0, 0, 0), m_z_order);
	}
	void on_clicked(int ctrl_id, int param)
	{
		c_dialog::close_dialog(m_surface);
		((c_surface_transparent*)m_surface)->clear_layer(m_z_order);
	}
};

class c_my_ui : public c_wnd
{
public:
	void on_paint()
	{
		c_image::draw_image(s_surface, Z_ORDER_LEVEL_0, c_theme::get_image(IMAGE_CUSTOM1), 0, 0);
	}
	virtual void on_init_children(void)
	{
		c_wave_ctrl* p_wave = (c_wave_ctrl*)get_wnd_ptr(ID_WAVE);
		p_wave->set_wave_speed(1);
		p_wave->set_wave_color(GL_RGB(0, 255, 0));
		p_wave->set_wave_in_out_rate(256, 17);
		p_wave->set_wave(&m_wave_buffer);
		p_wave->set_max_min(170, 110);
	}
	c_wave_buffer m_wave_buffer;
};

// Layout Widgets
static c_my_ui s_my_ui;
static c_my_dialog s_my_dialog;
static c_button s_button;
static c_wave s_wave;

WND_TREE s_dialog_widgets[] =
{
	{(c_wnd*)&s_button, ID_BUTTON, "CLOSE", 90, 130, 200, 100, NULL},
	{NULL, 0 , 0, 0, 0, 0, 0}
};


WND_TREE s_main_widgets[] =
{
	{(c_wnd*)&s_wave, ID_WAVE, 0, 0, 0, UI_WIDTH, UI_HEIGHT},
	{(c_wnd*)&s_my_dialog, ID_DIALOG, 0, 100, 240, 350, 360, s_dialog_widgets},
	{NULL, 0 , 0, 0, 0, 0, 0}
};

// Create GUI
extern const LATTICE_FONT_INFO Consolas_24B;
extern const BITMAP_INFO background_bmp;
void load_resource()
{
	c_theme::add_font(FONT_DEFAULT, &Consolas_24B);
	c_theme::add_image(IMAGE_CUSTOM1, &background_bmp);
	c_theme::add_color(COLOR_WND_FONT, GL_RGB(255, 255, 255));
	c_theme::add_color(COLOR_WND_NORMAL, GL_RGB(0, 117, 107));
	c_theme::add_color(COLOR_WND_FOCUS, GL_RGB(0, 117, 107));
	c_theme::add_color(COLOR_WND_PUSHED, GL_RGB(0, 117, 107));
	c_theme::add_color(COLOR_WND_BORDER, GL_RGB(0, 117, 107));
}

void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes) {
	load_resource();

	s_surface = new c_surface_transparent(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_1);
	s_display = new c_display(phy_fb, screen_width, screen_height, s_surface);
	s_surface->correct_color_after_display();
	s_my_ui.set_surface(s_surface);

	s_my_ui.connect(NULL, ID_ROOT, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_main_widgets);
	s_my_ui.show_window();
		
	unsigned int data_index1 = 0;
	unsigned int wave_index = 0;
	while (1)
	{
		if (wave_index % 200 == 0)
		{
			c_dialog::open_dialog(&s_my_dialog);
		}

		s_my_ui.m_wave_buffer.write_wave_data(s_wave_data1[data_index1++ % sizeof(s_wave_data1)]);
		s_my_ui.m_wave_buffer.write_wave_data(s_wave_data1[data_index1++ % sizeof(s_wave_data1)]);
		s_my_ui.m_wave_buffer.write_wave_data(s_wave_data1[data_index1++ % sizeof(s_wave_data1)]);
		s_my_ui.m_wave_buffer.write_wave_data(s_wave_data1[data_index1++ % sizeof(s_wave_data1)]);
		s_wave.refresh_wave(wave_index++);
		thread_sleep(17);
	}
}

//////////////////////// interface for all platform ////////////////////////
void startHelloTransparent(void* phy_fb, int width, int height, int color_bytes) {
	create_ui(phy_fb, width, height, color_bytes);
}

void sendTouch2HelloTransparent(int x, int y, bool is_down)
{
	is_down ? s_my_ui.on_touch(x, y, TOUCH_DOWN) : s_my_ui.on_touch(x, y, TOUCH_UP);
}

void sendKey2HelloTransparent(unsigned int key)
{
	s_my_ui.on_navigate(NAVIGATION_KEY(key));
}

void* getUiOfHelloTransparent(int* width, int* height, bool force_update)
{
	return s_display->get_updated_fb(width, height, force_update);
}
