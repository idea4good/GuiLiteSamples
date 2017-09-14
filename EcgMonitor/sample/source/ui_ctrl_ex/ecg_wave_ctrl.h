#ifndef ECG_WAVE_CTRL_H_
#define ECG_WAVE_CTRL_H_

class c_ecg_wave_ctrl : public c_wave_ctrl
{
protected:
	virtual void on_paint(void);
	virtual c_wnd* clone(){return new c_ecg_wave_ctrl();}
	void draw_grid();
};

#endif /* ECG_WAVE_CTRL_H_ */
