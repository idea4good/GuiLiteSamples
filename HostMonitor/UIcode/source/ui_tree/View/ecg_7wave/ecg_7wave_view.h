#ifndef __ECG_FULL_SCREEN_VIEW_H__
#define __ECG_FULL_SCREEN_VIEW_H__

class c_ecg_7wave_screen_view: public c_wnd
{
protected:	
	virtual void on_init_children(void);
	virtual c_wnd* clone(){return new c_ecg_7wave_screen_view();}
};
#endif
