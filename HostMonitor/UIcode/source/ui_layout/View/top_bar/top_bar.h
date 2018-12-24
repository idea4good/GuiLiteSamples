#ifndef _TOP_BAR_H_
#define _TOP_BAR_H_

class c_top_bar : public c_wnd
{
public:
	static void sysinfo_timer_callback(void* ptmr, void* parg);
protected:
	c_wnd* clone(){return new c_top_bar();}
	virtual void on_init_children(void);
	virtual void on_paint(void);
	void on_refurbish_time(unsigned int wParam, unsigned int lParam);
	GL_DECLARE_MESSAGE_MAP()
};

#endif
