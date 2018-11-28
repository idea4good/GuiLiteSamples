#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/msg.h"
#include "core_include/surface.h"
#include "core_include/display.h"
#include "gui_include/button.h"
#include "gui_include/gesture.h"

const int UI_WIDTH = 1024;
const int UI_HEIGHT = 768;
void* s_phy_fb;

class c_root : public c_wnd
{
	virtual c_wnd* clone() { return new c_root(); }
};

static c_root s_root;
static c_button s_start_button;
static WND_TREE s_root_children[] =
{
	//start button
	{(c_wnd*)&s_start_button, 2, 0, 0, 0, 0, NULL},
	{ NULL,0,0,0,0,0,0 }
};

void create_ui(int screen_width, int screen_height)
{
	c_display* display = new c_display(s_phy_fb, screen_width, screen_height, UI_WIDTH, UI_HEIGHT, 2, 0);
	c_surface* surface = display->create_surface(&s_root, Z_ORDER_LEVEL_1);
	surface->set_active(true);

	s_root.set_surface(surface);
	s_root.connect(NULL, 1, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_root_children);
	s_root.show_window();

	new c_gesture(&s_root, NULL, display->get_hid_pipe());
}
