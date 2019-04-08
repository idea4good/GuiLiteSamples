#ifndef _WAVE_CTRL_EX_H_
#define _WAVE_CTRL_EX_H_

class c_ecg_wave_ctrl : public c_wave_ctrl
{
protected:
	virtual void on_paint(void);
	virtual c_wnd* clone(){return new c_ecg_wave_ctrl();}
	void draw_grid();
};

///////////////////////////////////////////////////

#include "../core_include/theme.h"
class c_bitmap_wave_ctrl : public c_wave_ctrl
{
public:
	void set_bitmap(BITMAP_TYPE type) { m_bitmap_type = type; }
protected:
	virtual void on_paint(void);
	virtual c_wnd* clone() { return new c_bitmap_wave_ctrl(); }
private:
	BITMAP_TYPE m_bitmap_type;
};

#endif /* _WAVE_CTRL_EX_H_ */
