#ifndef _SCALE_BAR_H_
#define _SCALE_BAR_H_

#include "gui_include/button.h"

#define ND_SCALE_CLICKED							0x2013

#define ON_ND_SACLE_CLICKED(ctrlId, func)           \
{MSG_TYPE_WND, ND_SCALE_CLICKED, (c_cmd_target*)ctrlId, MSG_CALLBACK_VWV, (MsgFuncVV)(static_cast<void (c_cmd_target::*)(unsigned int)>(&func))},

class c_time_bar : public c_wnd
{
public:
	virtual c_wnd* clone(){return new c_time_bar();}
	virtual void on_init_children();
	virtual void on_paint(void);
	void set_time(long time);//time unit: second
	long get_start_time(){return m_start_seconds;}
	long get_end_time(){return m_end_seconds;}	
private:
	int set_scale_bar_atrrs(long start_time, long end_time, unsigned int color, const GUI_FONT* font);//time unit: second
	void draw_scale();
	void draw_mark();
	unsigned int time_2_pos_x(int time_minute);
	void on_btn_click(unsigned int ctrl_id);
private:
	unsigned int m_scale_color;
	const GUI_FONT* m_mark_font;
	
	long m_end_seconds;
	long m_start_seconds;
	int m_scale_resolution;

	c_button m_backward;
	c_button m_fast_backward;
	c_button m_forward;
	c_button m_fast_forward;
	GLT_DECLARE_MESSAGE_MAP()
};

#endif
