#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/surface.h"
#include "core_include/resource_type.h"
#include "core_include/word.h"
#include "gui_include/font.h"
#include "../include/ctrl_id.h"
#include "../source/resource/font/strings.h"
#include "gui_include/table.h"
#include <stdio.h>
#include "trend_table.h"

void c_trend_table::on_init_children(void)
{
	m_font_color = GLT_RGB(255, 255, 255);
	m_bg_color = GLT_RGB(80, 87, 104);

	m_align_type = ALIGN_LEFT | ALIGN_VCENTER;
	m_font_type = FONT_ENG_SMB_AA();

	set_col_num(9);
	set_row_num(9);
	set_col_width(63);
	set_col_width(0, 130);
	set_row_height(30);
}

void c_trend_table::on_paint(void)
{//For initialize
	set_item(0, 0, (char*)" - Tabular", ROW_ODD_COLOR);
	set_item(1, 0, (char*)" - Vital", ROW_EVEN_COLOR);
	set_item(2, 0, (char*)"   HR  ", ROW_ODD_COLOR);
	set_item(3, 0, (char*)"   SPO2 %", ROW_EVEN_COLOR);
	set_item(4, 0, (char*)"   Resp  ", ROW_ODD_COLOR);
	set_item(5, 0, (char*)"   PR", ROW_EVEN_COLOR);
	set_item(6, 0, (char*)"   Nibp(sys)", ROW_ODD_COLOR);
	set_item(7, 0, (char*)"   Nibp(mean)", ROW_EVEN_COLOR);
	set_item(8, 0, (char*)"   Nibp(dia)", ROW_ODD_COLOR);

	T_TIME st_time;
	unsigned int color;
	char str_buf[32];
	long start_time = (get_time_in_second() - ((TREND_TABLE_DATA_CNT - 1) * 60));
	for (int i = 1; i <= TREND_TABLE_DATA_CNT; i++)
	{
		color = (i % 2) ? ROW_EVEN_COLOR : ROW_ODD_COLOR;
		if (i == TREND_TABLE_DATA_CNT) { color = LATEST_COL_COLOR; }

		// 1st row
		st_time = second_to_day((start_time + (i - 1) * 60));
		sprintf(str_buf, "   %02d:%02d ", st_time.hour, st_time.minute);
		set_item(0, i, str_buf, color);
		// 2nd row
		set_item(1, i, (char*)"    ", color);//for vital - tbd
	}

	//data rows
	for (int i = 0; i < 7; i++)
	{
		for (int j = 1; j <= TREND_TABLE_DATA_CNT; j++)
		{
			color = (j % 2) ? ROW_EVEN_COLOR : ROW_ODD_COLOR;
			if (j == 8) { color = LATEST_COL_COLOR; }
			sprintf(str_buf, "      --- ");
			set_item((i + 2), j, str_buf, color);
		}
	}
}