#ifndef _VALUE_SUB_CTRL_H_
#define _VALUE_SUB_CTRL_H_

class c_value_sub_ctrl : public c_value_ctrl
{
protected:
	virtual void on_paint(void);
	virtual c_wnd* clone() { return new c_value_sub_ctrl(); }
};

#endif
