#ifndef _PATIENT_VIEW_H_
#define _PATIENT_VIEW_H_

class c_patient_view : public c_wnd
{
protected:
	c_wnd* clone(){return new c_patient_view();}
	virtual void on_paint(void);
};

#endif
