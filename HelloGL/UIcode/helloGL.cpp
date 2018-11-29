#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/surface.h"
#include "core_include/resource.h"
#include "core_include/bitmap.h"
#include "core_include/msg.h"
#include "core_include/display.h"
#include "gui_include/my_resource.h"
#include "gui_include/button.h"
#include "gui_include/dialog.h"
#include "gui_include/gesture.h"
#include <stdlib.h>

const int UI_WIDTH = 1280;
const int UI_HEIGHT = 720;

//////////////////////// define widgets ////////////////////////
enum WND_ID
{
	ID_ROOT = 1,
	ID_DESKTOP,
	ID_START_BUTTON,
	ID_START_MENU
};
class c_root : public c_wnd
{
	virtual c_wnd* clone() { return new c_root(); }
};

class c_desktop : public c_wnd
{
	virtual c_wnd* clone() { return new c_desktop(); }
	virtual void on_paint(void);
	void on_clicked(unsigned int ctrl_id);
	GLT_DECLARE_MESSAGE_MAP()
};

GLT_BEGIN_MESSAGE_MAP(c_desktop)
ON_GLT_BN_CLICKED(ID_START_BUTTON, c_desktop::on_clicked)
GLT_END_MESSAGE_MAP()

void c_desktop::on_clicked(unsigned int ctrl_id)
{
	static bool is_open = false;
	(is_open) ? c_dialog::close_dialog(m_surface): c_dialog::open_dialog((c_dialog*)get_wnd_ptr(ID_START_MENU));
	is_open = !is_open;
}

void c_desktop::on_paint()
{
	c_rect rect;
	get_screen_rect(rect);
	c_bitmap::draw_bitmap(m_surface, m_z_order, c_my_resource::get_bmp(BITMAP_CUSTOM1), rect.m_left, rect.m_top);

	extern const BITMAP_INFO start_icon_bmp;
	extern const BITMAP_INFO start_icon_click_bmp;
	c_button* start_button = (c_button*)get_wnd_ptr(ID_START_BUTTON);
	start_button->set_bitmap(&start_icon_bmp);
	start_button->set_focus_bitmap(&start_icon_bmp);
	start_button->set_pushed_bitmap(&start_icon_click_bmp);
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
	c_bitmap::draw_bitmap(m_surface, m_z_order, c_my_resource::get_bmp(BITMAP_CUSTOM2), rect.m_left, rect.m_top);
}


//////////////////////// layout UI ////////////////////////
static c_root s_root;
static c_desktop s_desktop;
static c_button s_start_button;
static c_start_menu s_start_menu;

static WND_TREE s_desktop_children[] =
{
	{(c_wnd*)&s_start_menu, ID_START_MENU, 0, 0, 100, 650, 580, NULL},
	{(c_wnd*)&s_start_button, ID_START_BUTTON, 0, 0, 682, 47, 38, NULL},
	{ NULL,0,0,0,0,0,0 }
};

static WND_TREE s_root_children[] =
{
	//start button
	{(c_wnd*)&s_desktop, ID_DESKTOP, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_desktop_children},
	{ NULL,0,0,0,0,0,0 }
};

//////////////////////// start UI ////////////////////////
extern const BITMAP_INFO desktop_bmp;
extern const BITMAP_INFO start_menu_bmp;
void load_resource()
{
	c_my_resource::add_bitmap(BITMAP_CUSTOM1, &desktop_bmp);
	c_my_resource::add_bitmap(BITMAP_CUSTOM2, &start_menu_bmp);

	c_my_resource::add_color(CTRL_FORE_GROUND, GL_RGB(36, 36, 36));
	c_my_resource::add_color(CTRL_BACK_GROUND, GL_RGB(255, 255, 255));
}

void create_ui(int screen_width, int screen_height, int color_bytes)
{
	load_resource();

	void* s_phy_fb = calloc(screen_width * screen_height, color_bytes);
	c_display* display = new c_display(s_phy_fb, screen_width, screen_height, UI_WIDTH, UI_HEIGHT, color_bytes, 0);
	c_surface* surface = display->create_surface(&s_root, Z_ORDER_LEVEL_1);
	surface->set_active(true);

	s_root.set_surface(surface);
	s_root.connect(NULL, ID_ROOT, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_root_children);
	s_root.show_window();

	new c_gesture(&s_root, NULL, display->get_hid_pipe());
}

//////////////////////// interface for all platform ////////////////////////
int start_helloGL(int width, int height, int color_bytes)
{
	create_ui(width, height, color_bytes);
	return 0;
}

int sendTouch2helloGL(void* buf, int len, int display_id)
{
	if (len != sizeof(MSG_INFO))
	{
		ASSERT(FALSE);
	}
	return c_hid_pipe::write_hid_msg((MSG_INFO*)buf, display_id);
}

void* getUiOfhelloGL(int* width, int* height)
{
	return c_display::get_frame_buffer(0, width, height);
}