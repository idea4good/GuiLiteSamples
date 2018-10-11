#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../gui_include/table.h"
#include "../gui_include/my_resource.h"
#include "../include/ctrl_id.h"
#include "../include/msg_id.h"
#include "../source/data/database.h"
#include "../source/ui_ctrl_ex/trend_graph.h"
#include "../source/ui_ctrl_ex/trend_table.h"
#include "../source/ui_ctrl_ex/time_bar.h"
#include <stdio.h>
#include "mini_trend_view.h"

#define HR_COLOR				GL_RGB(148,251,78)
#define SPO2_COLOR				GL_RGB(90,166,247)
#define RR_COLOR				GL_RGB(255,255,82)

#define H_AXIS_MARK_CNT			7
#define H_AXIS_MARK_INTERVAL	(60 * 10)	//10 minutes between 2 marks
#define V_AXIS_HEIGHT			280

GLT_BEGIN_MESSAGE_MAP(c_trend_view_mini)
ON_GLT_USER_MSG(USR_MSG_UPDATE_TREND_VIEW, c_trend_view_mini::on_update_trend_view)
GLT_END_MESSAGE_MAP()

void c_trend_view_mini::on_init_children(void)
{
	c_trend_graph*	p_trend_graph = (c_trend_graph*)get_wnd_ptr(ID_TREND_SCREEN_VITAL_TREND_CTRL);
	p_trend_graph->set_type(TREND_TYPE_VITAL);
	p_trend_graph->set_v_axis_height(V_AXIS_HEIGHT);
}

void c_trend_view_mini::on_update_trend_view(unsigned int wParam, unsigned int lParam)
{
	long time = get_time_in_second();

	c_trend_graph*	p_vitals_trend_graph = (c_trend_graph*)get_wnd_ptr(ID_TREND_SCREEN_VITAL_TREND_CTRL);
	if (!p_vitals_trend_graph)
	{
		ASSERT(FALSE);
		return;
	}
	
	//update axis
	long x_axis_marks[H_AXIS_MARK_CNT];
	for (long i = 0; i < H_AXIS_MARK_CNT; i++)
	{
		x_axis_marks[(H_AXIS_MARK_CNT - 1) - i] = (time - (i * H_AXIS_MARK_INTERVAL));
	}
	p_vitals_trend_graph->set_h_axis_atrrs(c_my_resource::get_font(FONT_ENG_SB), x_axis_marks, H_AXIS_MARK_CNT);
	p_vitals_trend_graph->draw_h_axis();

	//update data
	int data[7][MAX_TREND_DATA_CNT];//hr, spo2, rr, pr, sys, dia, mean
	long start_time = (time - (H_AXIS_MARK_CNT - 1) * H_AXIS_MARK_INTERVAL);
	read_trend_data(start_time, time,
					data[0], data[1], data[2], data[3], data[4], data[5], data[6],
					MAX_TREND_DATA_CNT);
	//draw vital trend
	p_vitals_trend_graph->draw_line(0, 0, data[0], MAX_TREND_DATA_CNT, HR_COLOR );
	p_vitals_trend_graph->draw_line(1, 1, data[1], MAX_TREND_DATA_CNT, SPO2_COLOR);
	p_vitals_trend_graph->draw_line(2, 2, data[2], MAX_TREND_DATA_CNT, RR_COLOR );
}

int c_trend_view_mini::read_trend_data(long start_time, long end_time, int hr[], int spo2[], int rr[], int pr[],
						int nibp_sys[], int nibp_dia[], int nibp_mean[], int len)
{
	static VALUE_SET data[60];
	if ((0 >= len) || (len > (sizeof(data) / sizeof(VALUE_SET))))
	{
		ASSERT(FALSE);
		return 0;
	}

	int read_cnt = c_database::get_instance()->read(start_time, end_time, data, len);
	if (read_cnt > len)
	{
		ASSERT(FALSE);
	}

	long time = start_time;
	long detal = (end_time - start_time) / len;
	for (size_t i = 0; i < len; i++)
	{
		size_t j = 0;
		for (; j < read_cnt; j++)
		{
			if ((data[j].time >= time) && ((data[j].time - 60) <= time))
			{
				break;
			}
		}

		if (j == read_cnt)
		{
			hr[i] = rr[i] = spo2[i] = pr[i] = nibp_sys[i] = nibp_mean[i] = nibp_dia[i] = XXX;
		}
		else
		{
			hr[i] = data[j].hr;
			rr[i] = data[j].rr;
			spo2[i] = data[j].spo2;
			pr[i] = data[j].pr;
			nibp_sys[i] = data[j].nibp_sys;
			nibp_mean[i] = data[j].nibp_mean;
			nibp_dia[i] = data[j].nibp_dia;
		}
		time += detal;
	}

	return read_cnt;
}
