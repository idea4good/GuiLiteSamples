#ifndef _ECG_VALUE_VIEW_H_
#define _ECG_VALUE_VIEW_H_

class c_ecg_value_view : public c_value_view
{
public:
	virtual c_wnd* clone(){return new c_ecg_value_view();}
	virtual void on_init_children(void);
};

#endif
