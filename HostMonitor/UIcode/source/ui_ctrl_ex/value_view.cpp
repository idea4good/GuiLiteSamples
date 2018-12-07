#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../source/manager/value_manager.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include <string.h>
#include "value_view.h"

c_value_view* c_value_view::ms_param_view_group[PARAM_VIEW_NUM];
bool c_value_view::ms_is_has_timer = FALSE;

void c_value_view::refresh_value(bool flash_or_not, unsigned int flash_color)
{
	c_wnd* p_child = m_top_child;
	c_value_manager* p_real_data_mag = c_value_manager::get_instance();
	short value;
	unsigned int value_id;
	while(p_child)
	{
		if (0 == strcmp(p_child->get_class_name(),"c_value_ctrl"))
		{
			value_id = ((c_value_ctrl*)p_child)->get_value_id();
			p_real_data_mag->get_value(value_id, value);
			((c_value_ctrl*)p_child)->refurbish_value(value, p_real_data_mag->get_real_data_digit(value_id), flash_or_not, flash_color);
		}
		p_child = p_child->get_next_sibling();
	}
}

int c_value_view::register_value_view(c_value_view* p_pm_view)
{
	int i;
	for(i = 0; i < PARAM_VIEW_NUM; i++)
	{
		if (p_pm_view == ms_param_view_group[i])
		{
			return -1;
		}
	}

	for(i = 0; i < PARAM_VIEW_NUM; i++)
	{
		if (0 == ms_param_view_group[i])
		{
			ms_param_view_group[i] = p_pm_view;
			break;
		}
	}

	if (!ms_is_has_timer)
	{
		register_timer(1000, c_value_view::refresh_group_value);
		ms_is_has_timer = TRUE;
	}
	return 1;
}

void c_value_view::refresh_group_value(void* ptmr, void* parg)
{
	static unsigned int s_sequnce;
	unsigned int flash_color = (s_sequnce++ % 2) ? GL_RGB(255, 0, 0) : GL_RGB(0, 0, 0);
	for(int i = 0; i < PARAM_VIEW_NUM; i++)
	{
		if (ms_param_view_group[i])
		{
			ms_param_view_group[i]->refresh_value(false, flash_color);
		}
	}
}
