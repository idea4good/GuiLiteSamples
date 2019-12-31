#ifndef _SCALE_BAR_H_
#define _SCALE_BAR_H_

#include "GuiLite.h"

#define ND_SCALE_CLICKED							0x2013

#define ON_ND_SACLE_CLICKED(func)           \
{MSG_TYPE_WND, ND_SCALE_CLICKED, 0, msgCallback(&func)},

class c_time_bar : public c_wnd
{
public:
	virtual void on_init_children();
	virtual void on_paint(void);
	void set_time(long time);//time unit: second
	long get_start_time(){return m_start_seconds;}
	long get_end_time(){return m_end_seconds;}	
private:
	int set_scale_bar_atrrs(long start_time, long end_time, unsigned int color, const FONT_INFO* font);//time unit: second
	void draw_scale();
	void draw_mark();
	unsigned int time_2_pos_x(int time_minute);
	void on_btn_click(int ctrl_id, int param);
private:
	unsigned int m_scale_color;
	const FONT_INFO* m_mark_font;
	
	long m_end_seconds;
	long m_start_seconds;
	int m_scale_resolution;

	c_button m_backward;
	c_button m_fast_backward;
	c_button m_forward;
	c_button m_fast_forward;
	GL_DECLARE_MESSAGE_MAP()
};

#endif
