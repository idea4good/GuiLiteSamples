#include "core_include/wave_buffer.h"

#ifndef _WAVE_MANAGE_H_
#define _WAVE_MANAGE_H_

#define WAVE_CTRL_MAX	16
#define	SPEED_X1		1
#define	SPEED_X2		2
#define	SPEED_X3		4
#define	SPEED_X4		8

typedef enum
{
	WAVE_ECG1,
	WAVE_ECG2,
	WAVE_ECG3,
	WAVE_ECG4,
	WAVE_ECG5,
	WAVE_ECG6,
	WAVE_ECG7,
	WAVE_SPO2,
	WAVE_RESP,
	WAVE_TYPE_MAX
}WAVE_TYPE;

typedef struct struct_gui_font	GUI_FONT;
typedef const GUI_FONT* (*PTR_FUNC_GET_FONT)();
typedef struct struct_wave_ctrl_discpritor
{
	unsigned char  		wave_id;
	unsigned short 		wave_name;
	unsigned short 		wave_unit;

	PTR_FUNC_GET_FONT	wave_name_font_type;
	PTR_FUNC_GET_FONT   wave_unit_font_type;

	unsigned int		wave_name_color;
	unsigned int 		wave_unit_color;
	unsigned int 		wave_color;

	int         		max_data;
	int         		min_data;
	int         		pivot_data;
	int					sample_rate;
}WAVE_CTRL_DISCPRITOR;

class c_wave_ctrl;
class c_wave_manage : public c_cmd_target
{
public:
	int register_wave_ctrl(WAVE_TYPE wave_ctrl_type, c_wave_ctrl* p_wave);
	int save_curve_data(WAVE_TYPE wave_type, short data);
	void refurbish_all_curve();
	void clean_all_wave(bool redraw = true);
	static c_wave_manage* get_instance()
	{
		static c_wave_manage s_the_wave_manager;
		return &s_the_wave_manager;
	}
private:
	c_wave_buffer	m_waves[WAVE_TYPE_MAX];
    c_wave_ctrl* 	m_wave_ctrls[WAVE_TYPE_MAX][WAVE_CTRL_MAX];

	c_wave_manage();
	c_wave_manage(const c_wave_manage&);
	c_wave_manage& operator=(const c_wave_manage&);
	~c_wave_manage(){}
};

#endif
