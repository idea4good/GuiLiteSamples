#ifndef _TEMP_VALUE_VIEW_H_
#define _TEMP_VALUE_VIEW_H_

class c_temp_value_view : public c_value_view
{
public:
	virtual void on_init_children(void);
	virtual c_wnd* clone(){return new c_temp_value_view();}
};

#endif
