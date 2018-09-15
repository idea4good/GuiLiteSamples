#include "../core_include/api.h"
#include "../core_include/cmd_target.h"
#include "../core_include/rect.h"
#include "../core_include/wnd.h"
#include "../core_include/resource_type.h"
#include "../gui_include/button.h"
#include "../gui_include/spinbox.h"
#include "../gui_include/font.h"

//fonts
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_8_11;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_9B_12;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_10B_13;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_12_16;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_13B_17;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_15B_20;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_17B_23;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_26B_35;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_40B_53;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_64B_85;
extern  const GUI_FONT GUI_FontHZ_Arial_Narrow_104B_139;
static void load_fonts()
{
	c_font::add_font(FONT_ENG_S, &GUI_FontHZ_Arial_Narrow_8_11);
	c_font::add_font(FONT_ENG_SB, &GUI_FontHZ_Arial_Narrow_9B_12);
	c_font::add_font(FONT_ENG_SBM, &GUI_FontHZ_Arial_Narrow_10B_13);
	c_font::add_font(FONT_ENG_SMB, &GUI_FontHZ_Arial_Narrow_12_16);

	c_font::add_font(FONT_ENG_SMB_AA, &GUI_FontHZ_Arial_Narrow_13B_17);
	c_font::add_font(FONT_ENG_MB_AA, &GUI_FontHZ_Arial_Narrow_15B_20);
	c_font::add_font(FONT_ENG_MMB_AA, &GUI_FontHZ_Arial_Narrow_17B_23);
	c_font::add_font(FONT_ENG_MB, &GUI_FontHZ_Arial_Narrow_26B_35);

	c_font::add_font(FONT_ENG_LLB, &GUI_FontHZ_Arial_Narrow_40B_53);
	c_font::add_font(FONT_ENG_LLLB, &GUI_FontHZ_Arial_Narrow_64B_85);
	c_font::add_font(FONT_ENG_LLLLB, &GUI_FontHZ_Arial_Narrow_104B_139);
}

//icons
extern const GUI_BITMAP bmspin_up_button_normal;
extern const GUI_BITMAP bmspin_up_button_focus;
extern const GUI_BITMAP bmspin_down_button_normal;
extern const GUI_BITMAP bmspin_down_button_focus;
static void load_icons()
{
	c_spin_box::ms_bt_up_normal_icon = &bmspin_up_button_normal;
	c_spin_box::ms_bt_up_focus_icon = &bmspin_up_button_focus;
	c_spin_box::ms_bt_down_normal_icon = &bmspin_down_button_normal;
	c_spin_box::ms_bt_down_focus_icon = &bmspin_down_button_focus;
}

//shapes

void load_theme()
{
	load_fonts();
	load_icons();
}