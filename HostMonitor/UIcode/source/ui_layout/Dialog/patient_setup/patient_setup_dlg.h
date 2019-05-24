#ifndef _SETUP_DLG_H_
#define _SETUP_DLG_H_

class c_patient_setup_dlg: public c_dialog
{
protected:
    void patient_dlg_crtl_init(void);
    virtual c_wnd* clone(){return new c_patient_setup_dlg();}
	virtual void on_paint(void);
};

#endif
