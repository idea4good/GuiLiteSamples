#ifndef _TREND_TABLE_H_
#define _TREND_TABLE_H_

#define TREND_TABLE_DATA_CNT		8
#define ROW_ODD_COLOR				GL_RGB(74,77,74)
#define ROW_EVEN_COLOR				GL_RGB(57,56,66)
#define LATEST_COL_COLOR			GL_RGB(99,65,33)

class c_trend_table : public c_table
{
	virtual c_wnd* clone() { return new c_trend_table(); }
	virtual void on_init_children(void);
	virtual void on_paint(void);
};

#endif // !TREND_TABLE_H
