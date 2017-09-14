#ifndef _ABOUT_DLG_H_
#define _ABOUT_DLG_H_

class c_about_dlg: public c_dialog
{
	virtual c_wnd* clone(){return new c_about_dlg();}
};

#endif
