#ifndef _VALUE_CTRL_H_
#define _VALUE_CTRL_H_

typedef struct
{
	unsigned short name_id;
	unsigned short unit_id;
	unsigned short   value_id;

	PTR_FUNC_GET_FONT name_font_type;
	PTR_FUNC_GET_FONT unit_font_type;
	PTR_FUNC_GET_FONT limit_font_type;
	PTR_FUNC_GET_FONT value_font_type;
	PTR_FUNC_GET_FONT value_big_font_type;

	unsigned int	name_color;
	unsigned int	unit_color;
	unsigned int	limit_color;
}VALUE_CTRL_XML;

class c_value_ctrl : public c_wnd
{
public:
	c_value_ctrl();
	virtual c_wnd* clone(){return new c_value_ctrl();}
	virtual void pre_create_wnd();
	virtual const char* get_class_name(void) const {return "c_value_ctrl";}
	void set_name(unsigned short str_id){m_name_id = str_id;}
	void set_unit_strid(unsigned short str_id){m_unit_strid = str_id;}
	void set_value_id(unsigned int value_id){ m_value_id = value_id;}
	unsigned int get_value_id(void){ return m_value_id;}

	void set_high_limit(short value, short dot_position){m_high_limit = value; m_limit_dot_position = dot_position;}
	void set_low_limit(short value, short dot_position){m_low_limit = value; m_limit_dot_position = dot_position;}
	void set_value_dot_position(unsigned short dot_position){m_value_dot_position = m_limit_dot_position = dot_position;}
	virtual void refurbish_value(short value, unsigned short dot_position, bool flash_or_not, unsigned int flash_color);

	void set_name_font_type(const GUI_FONT *name_font_type){m_name_font_type = name_font_type;}
	void set_unit_font_type(const GUI_FONT *unit_font_type){m_unit_font_type = unit_font_type;}
	void set_limit_font_type(const GUI_FONT *limit_font_type){m_limit_font_type = limit_font_type;}
	void set_value_font_type(const GUI_FONT *value_font_type){m_value_font_type = value_font_type;}

	void set_name_color(unsigned int color){m_name_color = color;}
	void set_unit_color(unsigned int color){m_unit_color = color;}
	void set_limit_color(unsigned int color){m_limit_color = color;}
protected:
	virtual void on_paint(void);

	short			m_value;
	unsigned short	m_value_dot_position;

	char            m_value_in_str[8];
	unsigned int	m_value_align_type;

	c_rect			m_value_rect;
	c_rect          m_max_value_rect;

	unsigned short	m_name_id;
	unsigned short	m_unit_strid;
	unsigned int	m_value_id;

	short			m_high_limit;
	short			m_low_limit;
	short			m_limit_dot_position;
	c_rect			m_limit_rect;

	const GUI_FONT *m_value_font_type;
	const GUI_FONT *m_name_font_type;
	const GUI_FONT *m_unit_font_type;
	const GUI_FONT *m_limit_font_type;

	unsigned int	m_name_color;
	unsigned int	m_unit_color;
	unsigned int	m_limit_color;
};

#endif
