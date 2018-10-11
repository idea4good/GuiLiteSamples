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
		c_my_resource::add_font(FONT_ENG_S, &Arial_16B);
		c_my_resource::add_font(FONT_ENG_SB, &Arial_16B);
		c_my_resource::add_font(FONT_ENG_SBM, &Arial_16B);
		c_my_resource::add_font(FONT_ENG_SMB, &Arial_16B);

		c_my_resource::add_font(FONT_ENG_MB, &Arial_32B);
		c_my_resource::add_font(FONT_ENG_LLB, &Arial_56B);
		c_my_resource::add_font(FONT_ENG_LLLB, &Arial_62B);
		//icon
		c_my_resource::add_bitmap(BITMAP_UP_BT_NORMAL, &bmspin_up_button_normal);
		c_my_resource::add_bitmap(BITMAP_UP_BT_FOCUS, &bmspin_up_button_focus);
		c_my_resource::add_bitmap(BITMAP_DOWN_BT_NORMAL, &bmspin_down_button_normal);
		c_my_resource::add_bitmap(BITMAP_DOWN_BT_FOCUS, &bmspin_down_button_focus);
		//shape
		c_my_resource::add_shape(BUTTON_NORMAL, shape_bt_normal);
		c_my_resource::add_shape(BUTTON_FOCUS, shape_bt_focus);
		c_my_resource::add_shape(BUTTON_PUSH, shape_bt_push);
		c_my_resource::add_shape(LIST_BOX_SELECT, shape_listbox_select);
		c_my_resource::add_shape(LIST_BOX_PUSH, shape_listbox_push);
		c_my_resource::add_shape(LIST_BOX_EXTEND, shape_listbox_extend);
		c_my_resource::add_shape(KEY_BUTTON_NORMAL, shape_keyboard_bt_normal);
		c_my_resource::add_shape(KEY_BUTTON_PUSH, shape_keyboard_bt_push);
		//color
		c_my_resource::add_color(CTRL_FORE_GROUND, GL_RGB(255, 255, 255));
		c_my_resource::add_color(CTRL_BACK_GROUND, GL_RGB(36, 36, 36));
		break;
	case 1:
		//font
		c_my_resource::add_font(FONT_ENG_S, &Arial_16B);
		c_my_resource::add_font(FONT_ENG_SB, &Arial_16B);
		c_my_resource::add_font(FONT_ENG_SBM, &Arial_16B);
		c_my_resource::add_font(FONT_ENG_SMB, &Arial_16B);

		c_my_resource::add_font(FONT_ENG_MB, &Arial_32B);
		c_my_resource::add_font(FONT_ENG_LLB, &Arial_56B);
		c_my_resource::add_font(FONT_ENG_LLLB, &Arial_62B);
		//icon
		c_my_resource::add_bitmap(BITMAP_UP_BT_NORMAL, &bmspin_up_button_normal);
		c_my_resource::add_bitmap(BITMAP_UP_BT_FOCUS, &bmspin_up_button_focus);
		c_my_resource::add_bitmap(BITMAP_DOWN_BT_NORMAL, &bmspin_down_button_normal);
		c_my_resource::add_bitmap(BITMAP_DOWN_BT_FOCUS, &bmspin_down_button_focus);
		//no shape
		//color
		c_my_resource::add_color(CTRL_FORE_GROUND, GL_RGB(36, 36, 36));
		c_my_resource::add_color(CTRL_BACK_GROUND, GL_RGB(255, 255, 255));
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	
}