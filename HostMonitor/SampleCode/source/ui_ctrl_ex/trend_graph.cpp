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
#include "trend_graph.h"
#include <string.h>
#include <stdio.h>

//work resolution:1024*768
#define H_AXIS_WIDTH			470
#define V_AXIS_HEIGHT			140
//Horizen axis
#define X_ORG_OF_H_AXIS			160
//Vertical axis
#define X_ORG_OF_V_AXIS_1		155
#define X_ORG_OF_V_AXIS_2		110
#define X_ORG_OF_V_AXIS_3		635
//Mark text
#define V_MARK_TEXT_LENGTH		24
#define SCALE_LINE_LENGTH		2
#define MAX_TITLE_CNT			6
#define TITLE_HEIGHT			20
#define MARGIN_OF_TITLE			2
//Color
#define HR_COLOR				GLT_RGB(148,251,78)
#define RR_COLOR				GLT_RGB(255,255,82)
#define SPO2_COLOR				GLT_RGB(90,166,247)
#define NIBP_COLOR				GLT_RGB(255,0,0)
#define H_AXIS_COLOR			GLT_RGB(123,121,123)
#define BACKGROUND_COLOR		GLT_RGB(24,24,24)

void c_trend_graph::on_init_children(void)
{
	m_type = TREND_TYPE_INVALID;

	m_h_axis_width = H_AXIS_WIDTH;
	m_h_axis_min = m_h_axis_max = m_h_scale_cnt = 0;
	memset(m_h_scale_value, 0, sizeof(m_h_scale_value));

	m_v_axis_height = V_AXIS_HEIGHT;
	m_org_y_of_h_axis = (m_v_axis_height + 10);
	m_org_x_of_h_axis = X_ORG_OF_H_AXIS;
	m_h_axis_mark_font = FONT_ENG_SB();

	for ( int i = 0; i < V_AXIS_CNT; i++ )
	{
		m_v_axis_min[i] = m_v_axis_max[i] = m_v_scale_cnt[i] = 0;
		m_v_axis_mark_font[i] = FONT_ENG_S();
	}
	memset(m_v_scale_value , 0 , sizeof( m_v_scale_value ));

	m_org_y_of_v_axis = (m_v_axis_height + 10);
	m_org_x_of_v_aixs[0] = X_ORG_OF_V_AXIS_1;
	m_org_x_of_v_aixs[1] = X_ORG_OF_V_AXIS_2;
	m_org_x_of_v_aixs[2] = X_ORG_OF_V_AXIS_3;

	m_v_axis_color[0] = m_v_axis_color[1] = m_v_axis_color[2] = HR_COLOR;

	memset(m_line_x_buf, 0, sizeof(m_line_x_buf));
	memset(m_line_y_buf, 0, sizeof(m_line_y_buf));
	memset(m_line_len, 0, sizeof(m_line_len));
}

void c_trend_graph::set_v_axis_height(int height)
{
	m_v_axis_height = height;
	m_org_y_of_v_axis = (m_v_axis_height + 10);
	m_org_y_of_h_axis = (m_v_axis_height + 10);
}

void c_trend_graph::set_h_axis_atrrs(const GUI_FONT* font, long scale_value[], int scale_count)
{
	if (!font || scale_count < 0  || scale_count > MAX_MARK_CNT)
	{
		ASSERT(FALSE);
	}
	if (scale_count == 0)
	{
		return;
	}

	m_h_axis_mark_font = font;
	m_h_scale_cnt = scale_count;
	m_h_scale_time_interval = (scale_value[1] - scale_value[0]);
	memcpy(m_h_scale_value, scale_value, (scale_count * sizeof(long)));
	m_h_axis_min = scale_value[0];
	m_h_axis_max = scale_value[scale_count - 1];
}

void c_trend_graph::set_v_axis_atrrs(unsigned int v_axis_index, unsigned int color, const GUI_FONT* font, int value_scale[], int scale_count)
{
	if ( !font || scale_count <= 0 || scale_count > MAX_MARK_CNT || v_axis_index >= V_AXIS_CNT )
	{
		ASSERT(FALSE);
	}
	m_v_axis_color[v_axis_index] = color;
	m_v_scale_cnt[v_axis_index] = scale_count;
	m_v_axis_mark_font[v_axis_index] = font;
	memcpy(m_v_scale_value[v_axis_index], value_scale, (scale_count * sizeof(int)));
	m_v_axis_min[v_axis_index] = value_scale[0];
	m_v_axis_max[v_axis_index] = value_scale[scale_count - 1];
}

void c_trend_graph::draw_h_axis(void)
{
	if (!m_h_scale_cnt || (m_h_axis_min > m_h_axis_max))
	{
		return;
	}
	c_rect rect;
	get_screen_rect(rect);
	//Draw x axis -- double line
	draw_hline((rect.m_left + m_org_x_of_h_axis), (rect.m_left + m_org_x_of_h_axis + m_h_axis_width), (rect.m_top + m_org_y_of_h_axis), H_AXIS_COLOR);
	draw_hline((rect.m_left + m_org_x_of_h_axis), (rect.m_left + m_org_x_of_h_axis + m_h_axis_width), (rect.m_top + m_org_y_of_h_axis + 1), H_AXIS_COLOR);

	//Draw mark
	char str_scale_value[16];
	int x_start, y_start, y_end;
	T_TIME st_time;
	float x_pixel_per_value = (float)(m_h_axis_width) / (float)(m_h_axis_max - m_h_axis_min);
	for ( int i = 0; i < m_h_scale_cnt; i++ )
	{
		x_start = rect.m_left + m_org_x_of_h_axis + (int)( x_pixel_per_value * (m_h_scale_value[i] - m_h_axis_min) );
		st_time = second_to_day(m_h_scale_value[i]);
		sprintf(str_scale_value,"   %02d:%02d ",st_time.hour, st_time.minute);

		y_start = rect.m_top + m_org_y_of_h_axis;
		y_end = y_start + SCALE_LINE_LENGTH;

		//Draw scale line
		draw_vline( x_start, y_start, y_end, H_AXIS_COLOR);
		draw_vline( x_start+1, y_start, y_end, H_AXIS_COLOR);
		//Draw mark
		c_word::draw_string(m_surface, m_z_order, str_scale_value, x_start - 20, y_start + 5, m_h_axis_mark_font, H_AXIS_COLOR, BACKGROUND_COLOR);
	}
}

void c_trend_graph::draw_v_axis(void)
{
	for ( int i = 0; i < V_AXIS_CNT; i++ )
	{
		draw_v_axis(i);
	}
}

void c_trend_graph::draw_v_axis(int index)
{
	if (!m_v_scale_cnt[index] || (m_v_axis_min[index] > m_v_axis_max[index]))
	{
		return;
	}

	c_rect rect;
	get_screen_rect(rect);
	
	int scale_line_left, scale_line_right, mark_text_x;
	int axis_line_x = rect.m_left + m_org_x_of_v_aixs[index];
	switch( index )
	{
	case 0://hr
	case 1://spo2
		scale_line_left =  axis_line_x - SCALE_LINE_LENGTH;
		scale_line_right =  axis_line_x;
		mark_text_x =  axis_line_x - V_MARK_TEXT_LENGTH;
		break;
	case 2://rr
		scale_line_left =  axis_line_x;
		scale_line_right =  axis_line_x + SCALE_LINE_LENGTH;
		mark_text_x =  scale_line_right + 1;
		break;
	default:
		break;
	}

	//draw axis line
	int line_bottom = rect.m_top + m_org_y_of_v_axis;
	draw_vline(axis_line_x, (line_bottom - m_v_axis_height), line_bottom, m_v_axis_color[index]);

	//draw mark & scale line
	char str_scale_value[8];
	float y_pixel_per_value = (float)(m_v_axis_height) / (float)(m_v_axis_max[index] - m_v_axis_min[index]);
	for ( int i = 0; i < m_v_scale_cnt[index]; i++ )
	{
		sprintf(str_scale_value,"%d",  m_v_scale_value[index][i]);
		int scale_line_y = rect.m_top + m_org_y_of_v_axis - (int)( y_pixel_per_value * (m_v_scale_value[index][i] - m_v_axis_min[index]));
		draw_hline( scale_line_left, scale_line_right, scale_line_y, m_v_axis_color[index] );//scale line
		c_word::draw_string(m_surface, m_z_order, str_scale_value, mark_text_x, (scale_line_y - 8), m_v_axis_mark_font[index], m_v_axis_color[index], BACKGROUND_COLOR);//mark
	}
}

void c_trend_graph::draw_line(unsigned int v_axis_index, unsigned int line_index, int data[], unsigned int len, unsigned int color)
{
	if ( v_axis_index > V_AXIS_CNT || len > MAX_TREND_DATA_CNT || line_index > MAX_LINE_CNT)
	{
		ASSERT(FALSE);
	}
	
	//Erase expired trend line.
	draw_line_by_pixel(m_line_x_buf[line_index], m_line_y_buf[line_index], m_line_len[line_index], BACKGROUND_COLOR);

	c_rect rect;
	get_screen_rect(rect);
	float x_interval = (float)(m_h_axis_width) / (float)(len - 1);
	float y_interval = (float)(m_v_axis_height) / (float)(m_v_axis_max[v_axis_index] - m_v_axis_min[v_axis_index]);

	m_line_len[line_index] = len;
	for(int i = 0; i < len; i++)
	{
		m_line_x_buf[line_index][i] = rect.m_left + m_org_x_of_h_axis + (int)(x_interval * i);

		if (data[i] < m_v_axis_min[v_axis_index] || data[i] > m_v_axis_max[v_axis_index])
		{
			m_line_y_buf[line_index][i] = XXX;
		}
		else
		{
			m_line_y_buf[line_index][i] = rect.m_top + m_org_y_of_v_axis - (int)( y_interval * ( data[i] - m_v_axis_min[v_axis_index] ) ) ;
		}
	}
	draw_line_by_pixel(m_line_x_buf[line_index], m_line_y_buf[line_index], len, color);
}

void c_trend_graph::draw_title(unsigned int row_index, unsigned int str_id, unsigned int color, const GUI_FONT* font)
{
	if (row_index >= MAX_TITLE_CNT || !font)
	{
		ASSERT(FALSE);
	}
	c_rect rect;
	get_screen_rect(rect);
	c_word::draw_string(m_surface, m_z_order, str_id, rect.m_left + MARGIN_OF_TITLE, (rect.m_top + TITLE_HEIGHT * row_index + 5), font, color, BACKGROUND_COLOR);
}

void c_trend_graph::draw_line_by_pixel(int* line_x_buf, int* line_y_buf, int len, unsigned int color)
{
	int last_valid_index = -1;
	for (int i = 0; i < len; i++)
	{
		if (line_y_buf[i] != XXX)
		{
			if(last_valid_index < 0)
			{
				last_valid_index = i;
				continue;
			}
			c_wnd::draw_line(line_x_buf[last_valid_index], line_y_buf[last_valid_index], line_x_buf[i], line_y_buf[i], color);
			last_valid_index = i;
		}
	}
}

void c_trend_graph::on_paint(void)
{
	c_rect rect;
	get_screen_rect(rect);
	fill_rect(rect.m_left, rect.m_top, rect.m_right, rect.m_bottom, BACKGROUND_COLOR);
	int hr_y_axis_scale[5] = { 0, 50, 100, 150, 180 };
	int rr_y_axis_scale[7] = { 0, 10, 20, 30, 40, 50, 60 };
	int spo2_y_axis_scale[7] = { 70, 75, 80, 85, 90, 95, 100 };
	int pressure_y_axis_scale[5] = { 0, 50, 100, 150, 180 };

	long* x_axis_marks = new long[m_h_scale_cnt];

	long end_time = get_time_in_second();
	for (long i = 0; i < m_h_scale_cnt; i++)
	{
		x_axis_marks[(m_h_scale_cnt - 1) - i] = (end_time - (i * m_h_scale_time_interval));
	}
	
	switch (m_type)
	{
	case TREND_TYPE_VITAL:
		draw_title(0, STR_TREND_VITALS_NAME, GLT_RGB(255, 255, 255), FONT_ENG_SB());
		draw_title(1, STR_TREND_HR_TITLE, HR_COLOR, FONT_ENG_SB());
		draw_title(2, STR_TREND_SPO2_TITLE, SPO2_COLOR, FONT_ENG_SB());
		draw_title(3, STR_TREND_RR_TITLE, RR_COLOR, FONT_ENG_SB());
		set_v_axis_atrrs(0, HR_COLOR, FONT_ENG_SB(), hr_y_axis_scale, 5);
		set_v_axis_atrrs(1, SPO2_COLOR, FONT_ENG_SB(), spo2_y_axis_scale, 7);
		set_v_axis_atrrs(2, RR_COLOR, FONT_ENG_SB(), rr_y_axis_scale, 7);
		set_h_axis_atrrs(FONT_ENG_SB(), x_axis_marks, m_h_scale_cnt);
		break;
	case TREND_TYPE_NIBP:
		draw_title(0, STR_TREND_PRESSURES_NAME, GLT_RGB(255, 255, 255), FONT_ENG_SB());
		draw_title(1, STR_TREND_PRESSURES_SYS_TITLE, NIBP_COLOR, FONT_ENG_SB());
		draw_title(2, STR_TREND_PRESSURES_DIA_TITLE, NIBP_COLOR, FONT_ENG_SB());
		draw_title(3, STR_TREND_PRESSURES_MEAN_TITLE, NIBP_COLOR, FONT_ENG_SB());
		set_v_axis_atrrs(0, NIBP_COLOR, FONT_ENG_SB(), pressure_y_axis_scale, 5);
		set_h_axis_atrrs(FONT_ENG_SB(), x_axis_marks, m_h_scale_cnt);
		break;
	default:
		return;
	}
	draw_h_axis();
	draw_v_axis();
	delete[]x_axis_marks;
}