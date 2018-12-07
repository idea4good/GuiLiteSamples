#ifndef _SPO2_WAVE_VIEW_H_
#define _SPO2_WAVE_VIEW_H_

class c_spo2_wave_view : public c_wnd
{
public:
	virtual c_wnd* clone(){return new c_spo2_wave_view();}
	virtual void on_init_children(void);
};

#endif
