#ifndef _TREND_VIEW_H_
#define _TREND_VIEW_H_

class c_trend_view : public c_wnd
{
	friend class c_time_bar;
public:
	virtual void on_init_children(void);
	virtual void on_paint(void);
private:
	void on_time_bar_change(int ctrl_id, int param);
	void on_update_trend_view(int id, int param);
	virtual void refresh_trend_table(long start_time, long end_time);//time unit: second
	virtual void refresh_trend_graphic(long time);//time unit: second
	int read_trend_data(long start_time, long end_time, int hr[], int spo2[], int rr[], int pr[],
						int nibp_sys[], int nibp_dia[], int nibp_mean[], int len);//time unit: second
	GL_DECLARE_MESSAGE_MAP()
};

#endif
