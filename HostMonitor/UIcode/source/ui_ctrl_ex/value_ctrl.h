#ifndef _VALUE_CTRL_H_
#define _VALUE_CTRL_H_

#include "../core_include/resource.h"
#include "../core_include/theme.h"

#define ATTR_VALUE	0x00000001L

typedef struct
{
	char*			name;
	char*			unit;
	unsigned short	value_id;

	FONT_TYPE name_font_type;
	FONT_TYPE unit_font_type;
	FONT_TYPE limit_font_type;
	FONT_TYPE value_font_type;

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
	void set_name(char* str){m_name_str = str;}
	void set_unit_str(char* str){m_unit_str = str;}
	void set_value_id(unsigned int value_id) { m_value_id = value_id; }
	unsigned int get_value_id(void) { return m_value_id; }

	void set_high_limit(short value, short dot_position){m_high_limit = value; m_limit_dot_position = dot_position;}
	void set_low_limit(short value, short dot_position){m_low_limit = value; m_limit_dot_position = dot_position;}
	void set_value_dot_position(unsigned short dot_position){m_value_dot_position = m_limit_dot_position = dot_position;}
	virtual void refresh_value(short value, unsigned short dot_position, bool flash_or_not, unsigned int flash_color);

	void set_name_font_type(const FONT_INFO *name_font_type){m_name_font_type = name_font_type;}
	void set_unit_font_type(const FONT_INFO *unit_font_type){m_unit_font_type = unit_font_type;}
	void set_limit_font_type(const FONT_INFO *limit_font_type){m_limit_font_type = limit_font_type;}
	void set_value_font_type(const FONT_INFO *value_font_type){m_value_font_type = value_font_type;}

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

	char*			m_name_str;
	char*			m_unit_str;
	unsigned int	m_value_id;
	
	short			m_high_limit;
	short			m_low_limit;
	short			m_limit_dot_position;
	c_rect			m_limit_rect;

	const FONT_INFO *m_value_font_type;
	const FONT_INFO *m_name_font_type;
	const FONT_INFO *m_unit_font_type;
	const FONT_INFO *m_limit_font_type;

	unsigned int	m_name_color;
	unsigned int	m_unit_color;
	unsigned int	m_limit_color;
};

#endif
