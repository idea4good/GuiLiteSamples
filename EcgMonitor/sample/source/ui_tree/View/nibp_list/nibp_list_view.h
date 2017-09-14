#ifndef _NIBPLIST_VIEW_H_
#define _NIBPLIST_VIEW_H_

class c_nibplist_view : public c_value_view
{
public:
	virtual c_wnd* clone(){return new c_nibplist_view();}
	virtual void on_init_children(void);
protected:
	virtual void on_paint();
private:
	int m_table_colnum;
	int m_table_rownum;
};

#endif
