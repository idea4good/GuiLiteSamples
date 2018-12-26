#include "../core_include/api.h"
#include "../core_include/cmd_target.h"
#include "../core_include/rect.h"
#include "../core_include/wnd.h"
#include "../core_include/resource.h"
#include "../gui_include/button.h"
#include "../gui_include/spinbox.h"
#include "../gui_include/my_resource.h"

//fonts
extern const FONT_INFO Arial_16B;
extern const FONT_INFO Arial_32B;
extern const FONT_INFO Arial_56B;
extern const FONT_INFO Arial_62B;

//icons
extern const BITMAP_INFO bmspin_up_button_normal;
extern const BITMAP_INFO bmspin_up_button_focus;
extern const BITMAP_INFO bmspin_down_button_normal;
extern const BITMAP_INFO bmspin_down_button_focus;
extern const BITMAP_INFO wave_background_1_bmp;
extern const BITMAP_INFO wave_background_2_bmp;

//shapes
extern COLOR_RECT shape_bt_normal[];
extern COLOR_RECT shape_bt_focus[];
extern COLOR_RECT shape_bt_push[];
extern COLOR_RECT shape_listbox_select[];
extern COLOR_RECT shape_listbox_push[];
extern COLOR_RECT shape_listbox_extend[];
extern COLOR_RECT shape_keyboard_bt_normal[];
extern COLOR_RECT shape_keyboard_bt_push[];

void load_theme(int index)
{
	switch (index)
	{
	case 0:
		//font
		c_my_resource::add_font(FONT_DEFAULT, &Arial_16B);
		c_my_resource::add_font(FONT_CUSTOM1, &Arial_32B);
		c_my_resource::add_font(FONT_CUSTOM2, &Arial_56B);
		c_my_resource::add_font(FONT_CUSTOM3, &Arial_62B);
		//icon
		c_my_resource::add_bitmap(BITMAP_UP_ARROW1, &bmspin_up_button_normal);
		c_my_resource::add_bitmap(BITMAP_UP_ARROW2, &bmspin_up_button_focus);
		c_my_resource::add_bitmap(BITMAP_DOWN_ARROW1, &bmspin_down_button_normal);
		c_my_resource::add_bitmap(BITMAP_DOWN_ARROW2, &bmspin_down_button_focus);
		c_my_resource::add_bitmap(BITMAP_CUSTOM1, &wave_background_1_bmp);
		c_my_resource::add_bitmap(BITMAP_CUSTOM2, &wave_background_2_bmp);
		//color
		c_my_resource::add_color(COLOR_WND_FONT, GL_RGB(255, 255, 255));
		c_my_resource::add_color(COLOR_WND_NORMAL, GL_RGB(59, 75, 94));
		c_my_resource::add_color(COLOR_WND_PUSHED, GL_RGB(33, 42, 53));
		c_my_resource::add_color(COLOR_WND_FOCUS, GL_RGB(43, 118, 219));
		c_my_resource::add_color(COLOR_WND_BORDER, GL_RGB(46, 59, 73));
		break;
	case 1:
		//font
		c_my_resource::add_font(FONT_DEFAULT, &Arial_16B);
		c_my_resource::add_font(FONT_DEFAULT, &Arial_16B);
		c_my_resource::add_font(FONT_DEFAULT, &Arial_16B);
		c_my_resource::add_font(FONT_DEFAULT, &Arial_16B);

		c_my_resource::add_font(FONT_CUSTOM1, &Arial_32B);
		c_my_resource::add_font(FONT_CUSTOM2, &Arial_56B);
		c_my_resource::add_font(FONT_CUSTOM3, &Arial_62B);
		//icon
		c_my_resource::add_bitmap(BITMAP_UP_ARROW1, &bmspin_up_button_normal);
		c_my_resource::add_bitmap(BITMAP_UP_ARROW2, &bmspin_up_button_focus);
		c_my_resource::add_bitmap(BITMAP_DOWN_ARROW1, &bmspin_down_button_normal);
		c_my_resource::add_bitmap(BITMAP_DOWN_ARROW2, &bmspin_down_button_focus);
		//color
		
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}