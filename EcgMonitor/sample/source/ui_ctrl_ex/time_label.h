#ifndef _TIME_LABEL_H_
#define  _TIME_LABEL_H_

class c_time_label: public c_wnd
{
public:
	virtual c_wnd* clone(){return new c_time_label();}
	virtual void on_init_children(void);
protected:
	virtual void on_paint(void);
private:
	T_TIME m_time;
};
#endif
