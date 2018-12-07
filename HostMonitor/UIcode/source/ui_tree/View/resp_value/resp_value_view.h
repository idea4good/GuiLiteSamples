#ifndef _RESP_VALUE_VIEW_H_
#define _RESP_VALUE_VIEW_H_

class c_resp_value_view : public c_value_view
{
public:
	virtual c_wnd* clone(){return new c_resp_value_view();}
	virtual void on_init_children(void);
};

#endif
