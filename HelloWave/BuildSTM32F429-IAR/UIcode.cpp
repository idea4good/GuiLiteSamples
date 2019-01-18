#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/surface.h"
#include "core_include/resource.h"
#include "core_include/bitmap.h"
#include "core_include/word.h"
#include "core_include/msg.h"
#include "core_include/display.h"
#include "core_include/wave_ctrl.h"
#include "core_include/wave_buffer.h"
#include "gui_include/my_resource.h"
#include "gui_include/button.h"
#include <stdlib.h>
#include <string.h>

const int UI_WIDTH = 240;
const int UI_HEIGHT = 320;
const char s_wave_data[] =
{
	0x21, 0x22, 0x23, 0x22, 0x21, 0x20, 0x1E, 0x1C,
	0x1B, 0x19, 0x18, 0x16, 0x14, 0x12, 0x11, 0x10,
	0x0F, 0x0D, 0x0C, 0x0A, 0x09, 0x07, 0x06, 0x05,
	0x04, 0x03, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x06, 0x0E, 0x18, 0x23, 0x2D, 0x37, 0x40,
	0x49, 0x51, 0x57, 0x5A, 0x5A, 0x59, 0x55, 0x50,
	0x49, 0x42, 0x3B, 0x34, 0x2F, 0x29, 0x24, 0x20,
	0x1F, 0x1e, 0x1d, 0x1f
};

//////////////////////// define widgets & map message ////////////////////////
enum WND_ID
{
	ID_ROOT = 1,
	ID_WAVE,
	ID_LABEL1,
	ID_LABEL2,
	ID_LABEL3,
	ID_BUTTON
};

class c_my_label : public c_wnd
{
	virtual c_wnd* clone() { return new c_my_label(); }
	virtual void pre_create_wnd() {	m_style = GL_ATTR_VISIBLE | ALIGN_VCENTER | ALIGN_HCENTER; }
	virtual void on_paint(void) {
		c_rect rect;
		get_screen_rect(rect);
		switch (m_resource_id)
		{
		case ID_LABEL1:
			c_word::draw_string_in_rect(m_surface, m_z_order, m_str, rect, c_my_resource::get_font(FONT_CUSTOM1), GL_RGB(81, 255, 0), GL_ARGB(0, 0, 0, 0), m_style);
			break;
		case ID_LABEL2:
			c_word::draw_string_in_rect(m_surface, m_z_order, m_str, rect, c_my_resource::get_font(FONT_CUSTOM1), GL_RGB(255, 0, 0), GL_ARGB(0, 0, 0, 0), m_style);
			break;
		default:
			c_word::draw_string_in_rect(m_surface, m_z_order, m_str, rect, c_my_resource::get_font(FONT_CUSTOM1), GL_RGB(41, 189, 189), GL_ARGB(0, 0, 0, 0), m_style);
			break;
		}
	}
};

class c_myUI : public c_wnd
{
	virtual c_wnd* clone() { return new c_myUI(); }
	virtual void on_init_children(void) {
		c_wave_ctrl *p_wave = (c_wave_ctrl*)get_wnd_ptr(ID_WAVE);
		p_wave->set_wave_speed(1);
		p_wave->set_wave_color(GL_RGB(41, 189, 189));
		p_wave->set_wave_in_out_rate(60, 17);
		p_wave->set_wave(&m_wave_buffer);
		p_wave->set_max_min_base(100, 0, 50);
	}
	virtual void on_paint(void)
	{
		c_rect rect;
		get_screen_rect(rect);
		fill_rect(rect, GL_RGB(33, 33, 33));
	}
	void on_clicked(unsigned int ctrl_id) {
		static int index;
		c_wave_ctrl *p_wave = (c_wave_ctrl*)get_wnd_ptr(ID_WAVE);
		switch (index) {
		case 0:
			p_wave->set_wave_color(GL_RGB(255, 0, 0));
			break;
		case 1:
			p_wave->set_wave_color(GL_RGB(255, 255, 0));
			break;
		case 2:
			p_wave->set_wave_color(GL_RGB(41, 189, 189));
			break;
		}
		index = (index + 1) % 3;
	}
public:
	c_wave_buffer m_wave_buffer;
	GL_DECLARE_MESSAGE_MAP()//delcare message
};

//map message
GL_BEGIN_MESSAGE_MAP(c_myUI)
ON_GL_BN_CLICKED(ID_BUTTON, c_myUI::on_clicked)
GL_END_MESSAGE_MAP()

//////////////////////// layout UI ////////////////////////
static c_myUI s_myUI;
static c_wave_ctrl s_wave;
static c_my_label s_label1;
static c_my_label s_label2;
static c_my_label s_label3;
static c_button s_button;
static WND_TREE s_myUI_children[] =
{
	{&s_label1, ID_LABEL1, "GuiLite", 0, 0, 240, 60, NULL},
	{&s_label2, ID_LABEL2, "\xe2\x9d\xa4", 0, 60, 240, 60, NULL},
	{&s_label3, ID_LABEL3, "STM32\xe2\x9c\x8c", 0, 120, 240, 60, NULL},
	{&s_wave, ID_WAVE, 0, 0, 180, 239, 100, NULL},
	{&s_button, ID_BUTTON, "\xe4\xbf\xae\xe6\x94\xb9\xe9\xa2\x9c\xe8\x89\xb2", 60, 280, 120, 39, NULL},
	{ NULL,0,0,0,0,0,0 }
};

//////////////////////// start UI ////////////////////////
extern const FONT_INFO Lucida_Console_48;
extern const FONT_INFO Microsoft_YaHei_25;
void load_resource()
{
	c_my_resource::add_font(FONT_DEFAULT, &Microsoft_YaHei_25);
	c_my_resource::add_font(FONT_CUSTOM1, &Lucida_Console_48);
	//for button
	c_my_resource::add_color(COLOR_WND_FONT, GL_RGB(255, 255, 255));
	c_my_resource::add_color(COLOR_WND_NORMAL, GL_RGB(59, 75, 94));
	c_my_resource::add_color(COLOR_WND_PUSHED, GL_RGB(33, 42, 53));
	c_my_resource::add_color(COLOR_WND_FOCUS, GL_RGB(43, 118, 219));
	c_my_resource::add_color(COLOR_WND_BORDER, GL_RGB(46, 59, 73));
}

void create_ui(int screen_width, int screen_height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op)
{
	load_resource();
	static c_display s_display(screen_width, screen_height, color_bytes, gfx_op);
	c_surface* surface = s_display.alloc_surface(&s_myUI, Z_ORDER_LEVEL_0);
	surface->set_active(true);
	s_myUI.set_surface(surface);
	s_myUI.connect(NULL, ID_ROOT, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_myUI_children);
	s_myUI.show_window();

	int data_index = 0;
	unsigned int wave_index = 0;
	while(1)
	{
		if (data_index == sizeof(s_wave_data))
		{
			data_index = 0;
		}
		s_myUI.m_wave_buffer.write_wave_data(s_wave_data[data_index++]);
		s_wave.refresh_wave(wave_index++);
		thread_sleep(17);
	}
}

//////////////////////// interface for all platform ////////////////////////
void startHelloMCU(int width, int height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op)
{
	create_ui(width, height, color_bytes, gfx_op);
}

extern "C" void sendTouch2HelloMCU(void* buf, int len)
{
	(((MSG_INFO*)buf)->dwMsgId == 0x4700) ?
		s_myUI.on_touch_down(((MSG_INFO*)buf)->dwParam1, ((MSG_INFO*)buf)->dwParam2) :
		s_myUI.on_touch_up(((MSG_INFO*)buf)->dwParam1, ((MSG_INFO*)buf)->dwParam2);
}