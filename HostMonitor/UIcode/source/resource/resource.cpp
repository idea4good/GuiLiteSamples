#include "../include/GuiLite.h"

//fonts
extern const LATTICE_FONT_INFO Arial_16B;
extern const LATTICE_FONT_INFO Arial_32B;
extern const LATTICE_FONT_INFO Arial_56B;
extern const LATTICE_FONT_INFO Arial_62B;

//icons
extern const BITMAP_INFO bmspin_up_button_normal;
extern const BITMAP_INFO bmspin_up_button_focus;
extern const BITMAP_INFO bmspin_down_button_normal;
extern const BITMAP_INFO bmspin_down_button_focus;
extern const BITMAP_INFO wave_background_1_bmp;
extern const BITMAP_INFO wave_background_2_bmp;

void load_theme(int index)
{
	switch (index)
	{
	case 0:
		//font
		c_theme::add_font(FONT_DEFAULT, &Arial_16B);
		c_theme::add_font(FONT_CUSTOM1, &Arial_32B);
		c_theme::add_font(FONT_CUSTOM2, &Arial_56B);
		c_theme::add_font(FONT_CUSTOM3, &Arial_62B);
		//icon
		c_theme::add_image(IMAGE_CUSTOM1, &wave_background_1_bmp);
		c_theme::add_image(IMAGE_CUSTOM2, &wave_background_2_bmp);
		//color
		c_theme::add_color(COLOR_WND_FONT, GL_RGB(255, 255, 255));
		c_theme::add_color(COLOR_WND_NORMAL, GL_RGB(59, 75, 94));
		c_theme::add_color(COLOR_WND_PUSHED, GL_RGB(33, 42, 53));
		c_theme::add_color(COLOR_WND_FOCUS, GL_RGB(43, 118, 219));
		c_theme::add_color(COLOR_WND_BORDER, GL_RGB(46, 59, 73));
		break;
	case 1:
		//font
		c_theme::add_font(FONT_DEFAULT, &Arial_16B);
		c_theme::add_font(FONT_DEFAULT, &Arial_16B);
		c_theme::add_font(FONT_DEFAULT, &Arial_16B);
		c_theme::add_font(FONT_DEFAULT, &Arial_16B);

		c_theme::add_font(FONT_CUSTOM1, &Arial_32B);
		c_theme::add_font(FONT_CUSTOM2, &Arial_56B);
		c_theme::add_font(FONT_CUSTOM3, &Arial_62B);
		//icon
		//color
		
		break;
	default:
		ASSERT(false);
		break;
	}
}