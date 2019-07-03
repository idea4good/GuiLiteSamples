#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/surface.h"
#include "core_include/resource.h"
#include "core_include/bitmap.h"
#include "core_include/msg.h"
#include "core_include/display.h"
#include "core_include/theme.h"
#include "widgets_include/button.h"
#include "widgets_include/dialog.h"
#include "widgets_include/gesture.h"
#include <stdlib.h>

const int UI_WIDTH = 1280;
const int UI_HEIGHT = 720;

//////////////////////// define widgets & map message ////////////////////////
enum WND_ID
{
	ID_DESKTOP = 1,
	ID_START_BUTTON,
	ID_START_MENU
};

class c_start_button : public c_button
{
	virtual c_wnd* clone() { return new c_start_button(); }
	virtual void on_paint()
	{
		c_rect rect;
		get_screen_rect(rect);

		extern const BITMAP_INFO start_icon_bmp;
		extern const BITMAP_INFO start_icon_click_bmp;
		switch (m_status)
		{
		case STATUS_NORMAL:
			c_bitmap::draw_bitmap(m_surface, m_z_order, &start_icon_bmp, rect.m_left, rect.m_top);
			break;
		case STATUS_FOCUSED:
			c_bitmap::draw_bitmap(m_surface, m_z_order, &start_icon_bmp, rect.m_left, rect.m_top);
			break;
		case STATUS_PUSHED:
			c_bitmap::draw_bitmap(m_surface, m_z_order, &start_icon_click_bmp, rect.m_left, rect.m_top);
			break;
		default:
			ASSERT(false);
			break;
		}
	}
};

class c_desktop : public c_wnd
{
	virtual c_wnd* clone() { return new c_desktop(); }
	virtual void on_paint(void);
	void on_clicked(unsigned int ctrl_id);
	GL_DECLARE_MESSAGE_MAP()//delcare message
};

//map message
GL_BEGIN_MESSAGE_MAP(c_desktop)
ON_GL_BN_CLICKED(ID_START_BUTTON, c_desktop::on_clicked)
GL_END_MESSAGE_MAP()

void c_desktop::on_clicked(unsigned int ctrl_id)
{
	static bool is_open = false;
	(is_open) ? c_dialog::close_dialog(m_surface): c_dialog::open_dialog((c_dialog*)get_wnd_ptr(ID_START_MENU), false);
	is_open = !is_open;
}

void c_desktop::on_paint()
{
	c_rect rect;
	get_screen_rect(rect);
	extern const BITMAP_INFO desktop_bmp;
	int block_width = 80;
	int block_height = 60;
	int block_rows = desktop_bmp.YSize / block_height;
	int block_cols = desktop_bmp.XSize / block_width;
	int block_sum = block_rows * block_cols;
	bool* block_map = (bool*)calloc(block_sum, sizeof(bool));

	int sum = 0;
	while (sum < block_sum)
	{
		int x = rand() % block_cols;
		int y = rand() % block_rows;
		if (block_map[x + (y * block_cols)] == false)
		{
			c_bitmap::draw_bitmap(m_surface, m_z_order, &desktop_bmp, rect.m_left + x * block_width, rect.m_top + y * block_height, x * block_width, y * block_height, block_width, block_height);
			block_map[x + (y * block_cols)] = true;
			sum++;
			thread_sleep(10);
		}
	}
	free(block_map);
}

class c_start_menu : public c_dialog
{
	virtual c_wnd* clone() { return new c_start_menu(); }
	virtual void on_paint(void);
};

void c_start_menu::on_paint(void)
{
	c_rect rect;
	get_screen_rect(rect);
	extern const BITMAP_INFO start_menu_bmp;
	c_bitmap::draw_bitmap(m_surface, m_z_order, &start_menu_bmp, rect.m_left, rect.m_top);
}

//////////////////////// layout UI ////////////////////////
static c_desktop s_desktop;
static c_start_button s_start_button;
static c_start_menu s_start_menu;

static WND_TREE s_desktop_children[] =
{
	{(c_wnd*)&s_start_menu, ID_START_MENU, 0, 0, 100, 650, 580, NULL},
	{(c_wnd*)&s_start_button, ID_START_BUTTON, 0, 0, 682, 47, 38, NULL},
	{ NULL,0,0,0,0,0,0 }
};

//////////////////////// start UI ////////////////////////
static c_fifo s_hid_fifo;
static c_display* s_display;
void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes)
{
	s_display = new c_display(phy_fb, screen_width, screen_height, UI_WIDTH, UI_HEIGHT, color_bytes, 1);
	c_surface* surface = s_display->alloc_surface(&s_desktop, Z_ORDER_LEVEL_1);
	surface->set_active(true);

	s_desktop.set_surface(surface);
	s_desktop.connect(NULL, ID_DESKTOP, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_desktop_children);
	s_desktop.show_window();

	new c_gesture(&s_desktop, NULL, &s_hid_fifo);
	while(1)
	{
		thread_sleep(1000000);
	}
}

//////////////////////// interface for all platform ////////////////////////
void start_helloGL(void* phy_fb, int width, int height, int color_bytes)
{
	create_ui(phy_fb, width, height, color_bytes);
}

int sendTouch2helloGL(void* buf, int len)
{
	ASSERT(len == sizeof(MSG_INFO));
	return s_hid_fifo.write(buf, len);
}

void* getUiOfhelloGL(int* width, int* height, bool force_update)
{
	return s_display->get_updated_fb(width, height, force_update);
}

int captureUiOfhelloGL()
{
	return s_display->snap_shot("snap_short.bmp");
}