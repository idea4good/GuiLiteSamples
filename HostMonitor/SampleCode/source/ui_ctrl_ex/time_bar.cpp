#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../core_include/resource.h"
#include "../core_include/word.h"
#include "../gui_include/button.h"
#include "../gui_include/my_resource.h"
#include <stdio.h>
#include "time_bar.h"

#define MARGIN_LEFT				83
#define MARGIN_RIGHT			83

#define MINI_SCALE_HEIGHT		4
#define NORMAL_SCALE_HEIGHT		7
#define TIME_MARK_CNT			8

#define BUTTON_LENGTH			41
#define	ID_BACKWARD_BTN			1
#define	ID_FAST_BACKWARD_BTN	2
#define	ID_FORWARD_BTN			3
#define	ID_FAST_FORWARD_BTN		4

GLT_BEGIN_MESSAGE_MAP(c_time_bar)
ON_GLT_BN_CLICKED(ID_BACKWARD_BTN, c_time_bar::on_btn_click)
ON_GLT_BN_CLICKED(ID_FAST_BACKWARD_BTN, c_time_bar::on_btn_click)
ON_GLT_BN_CLICKED(ID_FORWARD_BTN, c_time_bar::on_btn_click)
ON_GLT_BN_CLICKED(ID_FAST_FORWARD_BTN, c_time_bar::on_btn_click)
GLT_END_MESSAGE_MAP()

void c_time_bar::on_init_children()
{
	set_time(get_time_in_second());
	m_bg_color = GL_RGB(49, 49, 49);

	c_rect rect;
	get_screen_rect(rect);
	m_fast_backward.connect(this, ID_FAST_BACKWARD_BTN, "<<", 0, 0, BUTTON_LENGTH, rect.Height());
	m_backward.connect(this, ID_BACKWARD_BTN, "<", (BUTTON_LENGTH + 1), 0, BUTTON_LENGTH, rect.Height());
	m_forward.connect(this, ID_FORWARD_BTN, ">", (rect.Width() - 2 * BUTTON_LENGTH - 6), 0, BUTTON_LENGTH, rect.Height());
	m_fast_forward.connect(this, ID_FAST_FORWARD_BTN, ">>", (rect.Width() - BUTTON_LENGTH - 5), 0, BUTTON_LENGTH, rect.Height());
}

void c_time_bar::on_paint(void)
{
	c_rect rect;
	get_screen_rect(rect);
	fill_rect(rect.m_left + MARGIN_LEFT, rect.m_top, rect.m_right - MARGIN_RIGHT, rect.m_bottom, m_bg_color);
	draw_scale();
	draw_mark();
}

void c_time_bar::set_time(long time)
{
	set_scale_bar_atrrs((time - ((TIME_MARK_CNT - 1) * 60)), time, GL_RGB(255, 255, 255), c_my_resource::get_font(FONT_ENG_SB));
	draw_mark();
}

int c_time_bar::set_scale_bar_atrrs(long start_time, long end_time, unsigned int color, const FONT_INFO* font)
{
	if ( !font ||  end_time <= start_time)
	{
		ASSERT(FALSE);
		return -1;
	}
	m_end_seconds = end_time;
	m_start_seconds = start_time;
	m_scale_resolution = (end_time - start_time) / (TIME_MARK_CNT - 1);
	m_scale_color = color;
	m_mark_font = font;
	return 0;
}

unsigned int c_time_bar::time_2_pos_x(int time_seconds)
{
	if ( time_seconds > m_end_seconds || time_seconds < m_start_seconds )
	{
		ASSERT(FALSE);
		return -1;
	}
	c_rect rect;
	get_screen_rect(rect);
	
	unsigned int scale_bar_len = rect.m_right - rect.m_left - MARGIN_LEFT - MARGIN_RIGHT - 40;
	if ( time_seconds == m_start_seconds )
	{
		return (rect.m_left + MARGIN_LEFT + 20);
	}
	else if ( time_seconds == m_end_seconds )
	{
		return (rect.m_right - MARGIN_RIGHT - 20);
	}
	else
	{
		float pixel_per_value = (float)( scale_bar_len ) / (float)( m_end_seconds - m_start_seconds );
		return (rect.m_left + MARGIN_LEFT + (int)( pixel_per_value * ( time_seconds - m_start_seconds ) ) + 20);
	}
}

void c_time_bar::draw_scale()
{
	if (m_end_seconds <= m_start_seconds)
	{
		ASSERT(FALSE);
	}

	c_rect rect;
	get_screen_rect(rect);

	unsigned int i, j, x_pos[TIME_MARK_CNT];
	for (i = 0; i < TIME_MARK_CNT; i++)
	{	
		x_pos[i] = time_2_pos_x(m_scale_resolution * i + m_start_seconds);
	}
	
	//draw border
	draw_hline( rect.m_left + MARGIN_LEFT, rect.m_right - MARGIN_RIGHT, rect.m_top, m_scale_color );
	draw_hline( rect.m_left + MARGIN_LEFT, rect.m_right - MARGIN_RIGHT, rect.m_bottom, m_scale_color );
	draw_vline( x_pos[0], rect.m_top, rect.m_top + NORMAL_SCALE_HEIGHT, GL_RGB(255,255,255) );
	draw_vline( x_pos[0] + 1, rect.m_bottom - NORMAL_SCALE_HEIGHT, rect.m_bottom, GL_RGB(255,255,255) );

	float sub_scale_line_len = (float)((x_pos[1] - x_pos[0]) / 4.00);
	for ( i = 1; i < TIME_MARK_CNT; i++ )
	{
		for ( j = 1; j < 4; j++ )
		{//sub scale line
			draw_vline( (int)(x_pos[i-1] + sub_scale_line_len * j), rect.m_top + 1, rect.m_top + MINI_SCALE_HEIGHT, GL_RGB(117,117,117) );
			draw_vline( (int)(x_pos[i-1] + sub_scale_line_len * j), rect.m_bottom - MINI_SCALE_HEIGHT - 1 , rect.m_bottom, GL_RGB(117,117,117) );
		}
		//scale line
		draw_vline( x_pos[i], rect.m_top, rect.m_top + NORMAL_SCALE_HEIGHT, GL_RGB(255,255,255) );
		draw_vline( x_pos[i] + 1, rect.m_bottom - NORMAL_SCALE_HEIGHT, rect.m_bottom, GL_RGB(255,255,255) );
	}
}

void c_time_bar::draw_mark()
{
	if (m_end_seconds <= m_start_seconds)
	{
		ASSERT(FALSE);
	}

	c_rect rect;
	get_screen_rect(rect);

	char buf[8];
	for (int i = 0; i  < TIME_MARK_CNT; i++ )
	{
		long time_in_seconds = m_scale_resolution * i + m_start_seconds;
		T_TIME st_time = second_to_day(time_in_seconds);
		sprintf( buf, "%02d:%02d", st_time.hour, st_time.minute );
		c_word::draw_string(m_surface, m_z_order, buf, (time_2_pos_x(time_in_seconds) - 15), rect.m_top + NORMAL_SCALE_HEIGHT + 2, m_mark_font, m_scale_color, m_bg_color);
	}
}

void c_time_bar::on_btn_click(unsigned int ctrl_id)
{
	int increment;
	switch ( ctrl_id )
	{
	case ID_BACKWARD_BTN:
		increment = -m_scale_resolution;
		break;
	case ID_FAST_BACKWARD_BTN:
		increment = 0 - ( m_end_seconds - m_start_seconds );
		break;
	case ID_FORWARD_BTN:
		increment = m_scale_resolution;
		break;
	case ID_FAST_FORWARD_BTN:
		increment = ( m_end_seconds - m_start_seconds );
		break;
	default:
		ASSERT(FALSE);
		return;
	}
	m_end_seconds += increment;
	m_start_seconds += increment;
	draw_mark();
	notify_parent(ND_SCALE_CLICKED, get_id(), 0);
}
