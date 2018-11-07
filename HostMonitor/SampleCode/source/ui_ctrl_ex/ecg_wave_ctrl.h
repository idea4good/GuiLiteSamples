#ifndef ECG_WAVE_CTRL_H_
#define ECG_WAVE_CTRL_H_

class c_ecg_wave_ctrl : public c_wave_ctrl
{
protected:
	virtual void on_paint(void);
	virtual c_wnd* clone(){return new c_ecg_wave_ctrl();}
	void draw_grid();
};

///////////////////////////////////////////////////////////

class c_bitmap_wave_ctrl : public c_wave_ctrl
{
public:
	void set_bitmap(int index) { m_bitmap_index = index; }
protected:
	virtual void on_paint(void);
	virtual c_wnd* clone() { return new c_ecg_wave_ctrl(); }
private:
	int m_bitmap_index;
};
#endif /* ECG_WAVE_CTRL_H_ */
