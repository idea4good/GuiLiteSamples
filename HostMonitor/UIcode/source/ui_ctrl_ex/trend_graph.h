#ifndef _TREND_CTRL_H_
#define _TREND_CTRL_H_

#define V_AXIS_CNT				3
#define MAX_MARK_CNT			10
#define MAX_TREND_DATA_CNT		60
#define MAX_LINE_CNT			3
#define XXX -999

enum TREND_TYPE
{
	TREND_TYPE_INVALID,
	TREND_TYPE_VITAL,
	TREND_TYPE_NIBP
};

class c_trend_graph : public c_wnd
{
public:
	virtual c_wnd* clone(){return new c_trend_graph();}
	virtual void on_init_children(void);
	virtual void on_paint(void);

	void set_type(enum TREND_TYPE type) { m_type = type; }
	void set_v_axis_height(int height);
	void set_h_axis_atrrs(const FONT_INFO* font, long scale_value[], int scale_count);//time in seconds.
	void set_v_axis_atrrs(unsigned int v_axis_index, unsigned int color, const FONT_INFO* font, int scale_value[], int scale_count);
	void draw_line(unsigned int v_axis_index, unsigned int line_index, int data[], unsigned int len, unsigned int color);
	void draw_h_axis(void);
private:
	void draw_line_by_pixel(int* line_x_buf, int* line_y_buf, int len, unsigned int color);
    void draw_title(unsigned int row_index, char* str, unsigned int color, const FONT_INFO* font);
	void draw_v_axis(int index);
	void draw_v_axis(void);
private:
    int m_h_axis_width;
	long m_h_axis_min;
	long m_h_axis_max;
	long m_h_scale_value[MAX_MARK_CNT];
	int m_h_scale_cnt;
	int m_h_scale_time_interval;
	int m_org_y_of_h_axis;
	int m_org_x_of_h_axis;
	const FONT_INFO* m_h_axis_mark_font;

	int m_v_axis_height;
	int m_v_axis_min[V_AXIS_CNT];
	int m_v_axis_max[V_AXIS_CNT];
	int m_v_scale_value[V_AXIS_CNT][MAX_MARK_CNT];
	int m_v_scale_cnt[V_AXIS_CNT];
	int m_org_y_of_v_axis;
	int m_org_x_of_v_aixs[V_AXIS_CNT];
	const FONT_INFO* m_v_axis_mark_font[V_AXIS_CNT];
	unsigned int m_v_axis_color[V_AXIS_CNT];

	int m_line_x_buf[MAX_LINE_CNT][MAX_TREND_DATA_CNT];
	int m_line_y_buf[MAX_LINE_CNT][MAX_TREND_DATA_CNT];
	int m_line_len[MAX_LINE_CNT];

	enum TREND_TYPE m_type;
};

#endif
