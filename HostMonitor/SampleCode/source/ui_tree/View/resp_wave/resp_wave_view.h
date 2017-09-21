#ifndef _RESP_WAVE_VIEW_H_
#define _RESP_WAVE_VIEW_H_

class c_resp_wave_view : public c_wnd
{
public:
	c_wnd* clone(){return new c_resp_wave_view();}
	virtual void on_init_children(void);
};
#endif
