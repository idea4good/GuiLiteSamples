#ifndef _ECG_WAVE_VIEW_H_
#define _ECG_WAVE_VIEW_H_

class c_ecg_wave_view : public c_wnd
{
public:
	virtual c_wnd* clone(){return new c_ecg_wave_view();}
	virtual void on_init_children(void);
};

#endif
