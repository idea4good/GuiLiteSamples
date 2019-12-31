#include <stdio.h>
#include "GuiLite.h"

#define UI_WIDTH 680
#define UI_HEIGHT 512

enum WND_ID
{
	ID_ROOT = 1,
	ID_LABEL_1,
	ID_LABEL_2,
	ID_LABEL_3,
	ID_BUTTON,
	ID_SPIN_BOX,
	ID_LIST_BOX,
	ID_EDIT_1,
	ID_EDIT_2,
	ID_DIALOG,
	ID_DIALOG_BUTTON,
	ID_DIALOG_EXIT_BUTTON
};

static c_display* s_display;
static char str[16];
class c_my_ui : public c_wnd
{
	virtual void on_init_children() 
	{
		c_edit* edit = (c_edit*)get_wnd_ptr(ID_EDIT_1);
		edit->set_keyboard_style(STYLE_ALL_BOARD);

		edit = (c_edit*)get_wnd_ptr(ID_EDIT_2);
		edit->set_keyboard_style(STYLE_NUM_BOARD);

		c_list_box  *list_box = (c_list_box*)get_wnd_ptr(ID_LIST_BOX);
		list_box->clear_item();
		list_box->add_item((char*)"Item 0");
		list_box->add_item((char*)"Item 1");
		list_box->add_item((char*)"Item 2");
		list_box->select_item(0);

		c_spin_box  *spin_box = (c_spin_box*)get_wnd_ptr(ID_SPIN_BOX);
		spin_box->set_max_min(9, 0);
		spin_box->set_step(1);
		spin_box->set_value(5);
	}
	virtual void on_paint(void) 
	{
		m_surface->draw_rect(0, 0, UI_WIDTH - 1, UI_HEIGHT - 1, GL_RGB(0, 255, 0), Z_ORDER_LEVEL_0);
		m_surface->draw_rect(2, 2, UI_WIDTH - 3, UI_HEIGHT - 3, GL_RGB(0, 255, 0), Z_ORDER_LEVEL_0);
    }
	void on_button_clicked(int ctrl_id, int param)
	{
		static int s_cnt;
		sprintf(str, "%d click", ++s_cnt);
		c_label* label = (c_label*)get_wnd_ptr(ID_LABEL_1);
		label->set_str(str);
		label->show_window();

		switch (ctrl_id)
		{
		case ID_BUTTON:
			c_dialog::open_dialog((c_dialog*)get_wnd_ptr(ID_DIALOG), get_wnd_ptr(ctrl_id));
			break;
		}
	}
	void on_spinbox_change(int ctrl_id, int value)
	{
		c_label* label = (c_label*)get_wnd_ptr(ID_LABEL_2);
		label->set_str("change");
		label->show_window();
	}
	void on_listbox_confirm(int ctrl_id, int value)
	{
		sprintf(str, "choose %d", value);
		c_label* label = (c_label*)get_wnd_ptr(ID_LABEL_3);
		label->set_str(str);
		label->show_window();
	}
	GL_DECLARE_MESSAGE_MAP()//delcare message
};

GL_BEGIN_MESSAGE_MAP(c_my_ui)
ON_GL_BN_CLICKED(c_my_ui::on_button_clicked)
ON_SPIN_CHANGE(c_my_ui::on_spinbox_change)
ON_LIST_CONFIRM(c_my_ui::on_listbox_confirm)
GL_END_MESSAGE_MAP()

class c_my_dialog : public c_dialog
{
	void on_button_clicked(int ctrl_id, int param)
	{
		switch (ctrl_id)
		{
		case ID_DIALOG_EXIT_BUTTON:
			c_dialog::close_dialog(m_surface);
			break;
		default:
			break;
		}
	}
	GL_DECLARE_MESSAGE_MAP()//delcare message
};

GL_BEGIN_MESSAGE_MAP(c_my_dialog)
ON_GL_BN_CLICKED(c_my_dialog::on_button_clicked)
GL_END_MESSAGE_MAP()

// Layout Widgets
static c_my_ui s_my_ui;
static c_label s_label_1, s_label_2, s_label_3;
static c_button s_button;
static c_spin_box s_spin_box;
static c_list_box s_list_box;
static c_edit s_edit1, s_edit2;

static c_my_dialog s_my_dialog;
static c_button s_dialog_button;
static c_button s_dialog_exit_button;
WND_TREE s_dialog_widgets[] =
{
	{ &s_dialog_button,	ID_DIALOG_BUTTON,	"Button",	100, 100, 100, 50},
	{ &s_dialog_exit_button,	ID_DIALOG_EXIT_BUTTON,	"Exit",	100, 200, 100, 50},
	{NULL, 0 , 0, 0, 0, 0, 0}
};

WND_TREE s_main_widgets[] =
{
	{ &s_edit1,		ID_EDIT_1,	"ABC",	150, 10, 100, 50},
	{ &s_edit2,		ID_EDIT_2,	"123",	400, 10, 100, 50},

	{ &s_label_1,	ID_LABEL_1,	"label 1",	150, 100, 100, 50},
	{ &s_label_2,	ID_LABEL_2,	"label 2",	150, 170, 100, 50},
	{ &s_label_3,	ID_LABEL_3,	"label 3",	150, 240, 100, 50},

	{ &s_button,	ID_BUTTON,	"Dialog",	400, 100, 100, 50},
	{ &s_spin_box,	ID_SPIN_BOX,"spinBox",	400, 170, 100, 50},
	{ &s_list_box,	ID_LIST_BOX,"listBox",	400, 240, 100, 50},

	{ &s_my_dialog,	ID_DIALOG,	"Dialog",	200, 100, 280, 312, s_dialog_widgets},
	{NULL, 0 , 0, 0, 0, 0, 0}
};

// Create GUI
extern const FONT_INFO Consolas_24B;
void load_resource()
{
	c_theme::add_font(FONT_DEFAULT, &Consolas_24B);
	//for button
	c_theme::add_color(COLOR_WND_FONT, GL_RGB(255, 255, 243));
	c_theme::add_color(COLOR_WND_NORMAL, GL_RGB(59, 75, 94));
	c_theme::add_color(COLOR_WND_PUSHED, GL_RGB(33, 42, 53));
	c_theme::add_color(COLOR_WND_FOCUS, GL_RGB(78, 198, 76));
	c_theme::add_color(COLOR_WND_BORDER, GL_RGB(46, 59, 73));
}

void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes) {
	load_resource();

	s_display = new c_display(phy_fb, screen_width, screen_height, UI_WIDTH, UI_HEIGHT, color_bytes, 1, NULL);
	c_surface* s_surface = s_display->alloc_surface(Z_ORDER_LEVEL_2);
	s_surface->set_active(true);

	s_my_ui.set_surface(s_surface);
	s_my_ui.connect(NULL, ID_ROOT, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_main_widgets);
	s_my_ui.show_window();

	while(1)
	{
		thread_sleep(10000);
	}
}

//////////////////////// interface for all platform ////////////////////////
void startHelloWidgets(void* phy_fb, int width, int height, int color_bytes) {
	create_ui(phy_fb, width, height, color_bytes);
}

void sendTouch2HelloWidgets(int x, int y, bool is_down)
{
	is_down ? s_my_ui.on_touch(x, y, TOUCH_DOWN) : s_my_ui.on_touch(x, y, TOUCH_UP);
}

void sendKey2HelloWidgets(unsigned int key)
{
	s_my_ui.on_key(KEY_TYPE(key));
}

void* getUiOfHelloWidgets(int* width, int* height, bool force_update)
{
	return s_display->get_updated_fb(width, height, force_update);
}

int captureUiOfHelloWidgets()
{
	return s_display->snap_shot("snap_short.bmp");
}
