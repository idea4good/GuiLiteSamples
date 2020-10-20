#ifndef _TOP_BAR_H_
#define _TOP_BAR_H_

class c_top_bar : public c_wnd
{
public:
	static void sysinfo_timer_callback(void* param);
protected:
	virtual void on_init_children(void);
	virtual void on_paint(void);
};

#endif
