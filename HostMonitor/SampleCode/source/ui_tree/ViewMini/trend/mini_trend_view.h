#ifndef _TREND_VIEW_H_
#define _TREND_VIEW_H_

class c_trend_view_mini : public c_wnd
{
public:
	virtual void on_init_children(void);
	virtual c_wnd* clone(){return new c_trend_view_mini();}
private:
	void on_update_trend_view(unsigned int wParam, unsigned int lParam);
	int read_trend_data(long start_time, long end_time, int hr[], int spo2[], int rr[], int pr[],
						int nibp_sys[], int nibp_dia[], int nibp_mean[], int len);//time unit: second
	GL_DECLARE_MESSAGE_MAP()
};

#endif
