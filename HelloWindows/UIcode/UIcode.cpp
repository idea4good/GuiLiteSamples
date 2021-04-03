#define GUILITE_ON  //Do not define this macro once more!!!
#include "GuiLite.h"
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
	virtual void on_paint()
	{
		c_rect rect;
		get_screen_rect(rect);

		extern const BITMAP_INFO start_icon_bmp;
		extern const BITMAP_INFO start_icon_click_bmp;
		switch (m_status)
		{
		case STATUS_NORMAL:
			c_image::draw_image(m_surface, m_z_order, &start_icon_bmp, rect.m_left, rect.m_top);
			break;
		case STATUS_FOCUSED:
			c_image::draw_image(m_surface, m_z_order, &start_icon_bmp, rect.m_left, rect.m_top);
			break;
		case STATUS_PUSHED:
			c_image::draw_image(m_surface, m_z_order, &start_icon_click_bmp, rect.m_left, rect.m_top);
			break;
		default:
			ASSERT(false);
			break;
		}
	}
};

class c_desktop : public c_wnd
{
	virtual void on_init_children()
	{
		((c_button*)get_wnd_ptr(ID_START_BUTTON))->set_on_click((WND_CALLBACK)&c_desktop::on_clicked);
	}
	virtual void on_paint(void)
	{
		c_rect rect;
		get_screen_rect(rect);
		extern const BITMAP_INFO desktop_bmp;
		int block_width = 80;
		int block_height = 60;
		int block_rows = desktop_bmp.height / block_height;
		int block_cols = desktop_bmp.width / block_width;
		int block_sum = block_rows * block_cols;
		bool* block_map = (bool*)calloc(block_sum, sizeof(bool));
		if (!block_map) { return; }
		int sum = 0;
		while (sum < block_sum)
		{
			int x = rand() % block_cols;
			int y = rand() % block_rows;
			if (block_map[x + (y * block_cols)] == false)
			{
				c_image::draw_image(m_surface, m_z_order, &desktop_bmp, rect.m_left + x * block_width, rect.m_top + y * block_height, x * block_width, y * block_height, block_width, block_height);
				block_map[x + (y * block_cols)] = true;
				sum++;
				thread_sleep(10);
			}
		}
		free(block_map);
	}
	void on_clicked(int ctrl_id, int param)
	{
		static bool is_open = false;
		(is_open) ? c_dialog::close_dialog(m_surface) : c_dialog::open_dialog((c_dialog*)get_wnd_ptr(ID_START_MENU), false);
		is_open = !is_open;
	}
};

class c_start_menu : public c_dialog
{
	virtual void on_paint(void);
};

void c_start_menu::on_paint(void)
{
	c_rect rect;
	get_screen_rect(rect);
	extern const BITMAP_INFO start_menu_bmp;
	int step = 10;
	for (int i = 0; i < start_menu_bmp.height; i += step)
	{
		thread_sleep(10);
		c_image::draw_image(m_surface, m_z_order, &start_menu_bmp, rect.m_left, rect.m_top + i, 0, i, start_menu_bmp.width, step, GL_RGB(0, 0, 0));
	}
}

//////////////////////// layout UI ////////////////////////
static c_desktop s_desktop;
static c_start_button s_start_button;
static c_start_menu s_start_menu;

static WND_TREE s_desktop_children[] =
{
	{(c_wnd*)&s_start_menu, ID_START_MENU, 0, 400, 50, 475, 633, NULL},
	{(c_wnd*)&s_start_button, ID_START_BUTTON, 0, 0, 682, 47, 38, NULL},
	{ NULL,0,0,0,0,0,0 }
};

//////////////////////// start UI ////////////////////////
static c_display* s_display;
void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes)
{
	c_surface surface = c_surface(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_1);
	s_display = new c_display(phy_fb, screen_width, screen_height, &surface);

	s_desktop.set_surface(&surface);
	s_desktop.connect(NULL, ID_DESKTOP, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_desktop_children);
	s_desktop.show_window();

	while(1)
	{
		thread_sleep(1000000);
	}
}

//////////////////////// interface for all platform ////////////////////////
void startHelloWindows(void* phy_fb, int width, int height, int color_bytes)
{
	create_ui(phy_fb, width, height, color_bytes);
}

void sendTouch2HelloWindows(int x, int y, bool is_down)
{
    is_down ? s_desktop.on_touch(x, y, TOUCH_DOWN) : s_desktop.on_touch(x, y, TOUCH_UP);
}

void* getUiOfHelloWindows(int* width, int* height, bool force_update)
{
	return s_display->get_updated_fb(width, height, force_update);
}

int captureUiOfhelloWindows()
{
	return s_display->snap_shot("snap_short.bmp");
}
