#ifndef _NIBP_VALUE_VIEW_H_
#define _NIBP_VALUE_VIEW_H_

class c_nibp_value_view : public c_value_view
{
public:
	virtual c_wnd* clone(){return new c_nibp_value_view();}
	virtual void on_init_children(void);
};

#endif
