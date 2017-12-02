#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "gui_include/table.h"
#include "gui_include/font.h"

#include "../include/ctrl_id.h"
#include "../source/resource/font/strings.h"
#include "../source/ui_ctrl_ex/value_view.h"

#include "nibp_list_view.h"

void c_nibplist_view::on_init_children(void)
{
	c_rect rect;
	this->get_screen_rect(rect);

    c_table *p_table = (c_table*)get_wnd_ptr(ID_NIBP_LIST_VIEW_TABLE);
	if (p_table == NULL)
	{
		ASSERT(FALSE);
		return;
	}

	p_table->set_font_color(GLT_RGB(255,255,255));
	p_table->set_bg_color(GLT_RGB(0,0,0));

	int total_height = rect.Height();
	int total_width = rect.Width()-4;
	m_table_colnum = 3;
	int col_width = total_width/(m_table_colnum+3);

	p_table->set_font_type(FONT_ENG_SMB_AA());
	int row_height = 26;

	m_table_rownum = total_height / row_height;

	p_table->set_row_num(m_table_rownum);
	p_table->set_row_height(row_height);
	p_table->set_col_num(m_table_colnum);

	p_table->set_col_width(0, 3 * col_width);
	p_table->set_col_width(1, col_width);
	p_table->set_col_width(2, 2 * col_width);
}

void c_nibplist_view::on_paint()
{
	c_table *p_table = (c_table*)get_wnd_ptr(ID_NIBP_LIST_VIEW_TABLE);
	if (p_table == NULL)
	{
		ASSERT(FALSE);
		return;
	}

	p_table->set_item(0, 0, "NIBP List");
	p_table->set_item(0, 1, "PR");
	p_table->set_item(0, 2, "Time");

	for (unsigned int i = 1; i < (m_table_rownum - 1); i++)
	{
		p_table->set_item(i, 0, "120/80(100)");
		p_table->set_item(i, 1, "60");
		p_table->set_item(i, 2, "14:27:53");
	}
}
