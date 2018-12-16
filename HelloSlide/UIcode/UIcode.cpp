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
#include "gui_include/my_resource.h"
#include "gui_include/button.h"
#include "gui_include/slide_group.h"
#include "gui_include/gesture.h"
#include <stdlib.h>
#include <string.h>

const int UI_WIDTH = 512;
const int UI_HEIGHT = 768;

//////////////////////// define widgets & map message ////////////////////////
enum WND_ID
{
	ID_ROOT = 1,
	ID_PAGE1,
	ID_PAGE2,
	ID_PAGE3,
	ID_PAGE4,
	ID_PAGE5
};

class c_page : public c_wnd
{
	virtual c_wnd* clone() { return new c_page(); }
	virtual void on_paint();
};

void c_page::on_paint()
{
	c_rect rect;
	get_screen_rect(rect);
	const BITMAP_INFO* bmp = NULL;
	switch (m_resource_id)
	{
	case ID_PAGE1:
		bmp = c_my_resource::get_bmp(BITMAP_CUSTOM1);
		break;
	case ID_PAGE2:
		bmp = c_my_resource::get_bmp(BITMAP_CUSTOM2);
		break;
	case ID_PAGE3:
		bmp = c_my_resource::get_bmp(BITMAP_CUSTOM3);
		break;
	case ID_PAGE4:
		bmp = c_my_resource::get_bmp(BITMAP_CUSTOM4);
		break;
	case ID_PAGE5:
		bmp = c_my_resource::get_bmp(BITMAP_CUSTOM5);
		break;
	default:
		break;
	}
	c_bitmap::draw_bitmap(m_surface, m_z_order, bmp, rect.m_left, rect.m_top);
}

//////////////////////// layout UI ////////////////////////
c_page s_page1, s_page2, s_page3, s_page4, s_page5;
static c_slide_group s_root;
static WND_TREE s_root_children[] =
{
	{ NULL,0,0,0,0,0,0 }
};

//////////////////////// start UI ////////////////////////
extern const BITMAP_INFO ten_bmp, jack_bmp, queen_bmp, king_bmp, ace_bmp;
static c_fifo s_hid_fifo;
static c_display* s_display;
void load_resource()
{
	c_my_resource::add_bitmap(BITMAP_CUSTOM1, &ten_bmp);
	c_my_resource::add_bitmap(BITMAP_CUSTOM2, &jack_bmp);
	c_my_resource::add_bitmap(BITMAP_CUSTOM3, &queen_bmp);
	c_my_resource::add_bitmap(BITMAP_CUSTOM4, &king_bmp);
	c_my_resource::add_bitmap(BITMAP_CUSTOM5, &ace_bmp);
}

void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes)
{
	load_resource();
	s_display = new c_display(phy_fb, screen_width, screen_height, UI_WIDTH, UI_HEIGHT, color_bytes, (1 + 5)/*1 root + 5 pages*/);
	c_surface* surface = s_display->alloc_surface(&s_root, Z_ORDER_LEVEL_1);
	surface->set_active(true);

	s_root.set_surface(surface);
	s_root.connect(NULL, ID_ROOT, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_root_children);

	s_root.add_slide(&s_page1, ID_PAGE1, 0, 0, UI_WIDTH, UI_HEIGHT, NULL);
	s_root.add_slide(&s_page2, ID_PAGE2, 0, 0, UI_WIDTH, UI_HEIGHT, NULL);
	s_root.add_slide(&s_page3, ID_PAGE3, 0, 0, UI_WIDTH, UI_HEIGHT, NULL);
	s_root.add_slide(&s_page4, ID_PAGE4, 0, 0, UI_WIDTH, UI_HEIGHT, NULL);
	s_root.add_slide(&s_page5, ID_PAGE5, 0, 0, UI_WIDTH, UI_HEIGHT, NULL);
	s_root.set_active_slide(0);
	s_root.show_window();

	new c_gesture(&s_root, &s_root, &s_hid_fifo);
	while(1)
	{
		thread_sleep(1000000);
	}
}

//////////////////////// interface for all platform ////////////////////////
void startHelloSlide(void* phy_fb, int width, int height, int color_bytes)
{
	create_ui(phy_fb, width, height, color_bytes);
}

int sendTouch2HelloSlide(void* buf, int len)
{
	ASSERT(len == sizeof(MSG_INFO));
	return s_hid_fifo.write(buf, len);
}

void* getUiOfHelloSlide(int* width, int* height, bool force_update)
{
	return s_display->get_updated_fb(width, height, force_update);
}

int captureUiOfHelloSlide()
{
	return s_display->snap_shot("snap_short.bmp");
}