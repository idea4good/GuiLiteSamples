#ifndef _TIME_LABEL_H_
#define  _TIME_LABEL_H_

class c_time_label: public c_wnd
{
public:
	virtual void on_init_children(void);
protected:
	virtual void on_paint(void);
private:
	T_TIME m_time;
};
#endif
