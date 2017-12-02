#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/surface.h"
#include "core_include/wave_ctrl.h"
#include "gui_include/font.h"
#include "../source/resource/font/strings.h"
#include "../source/modules/demo_module.h"
#include <string.h>
#include <stdio.h>
#include "wave_manager.h"

static WAVE_CTRL_DISCPRITOR s_demo_wave_ctrl_discpritor[WAVE_TYPE_MAX] =
{	/*wave data*/    	/*name*/	    /*unit*/	/*name_font*/  		/*unit_font*/      /*name_color*/		/*unit_color*/		  /*wave_color*/			/*max*/		/*min*/  /*pivot*/ /*sample rate*/
	{ WAVE_ECG1, STR_WAVE_NAME_ECG_I,	STR_NULL,	FONT_ENG_SMB_AA,	FONT_ENG_SB,	   GLT_RGB(0,255,0),		GLT_RGB(0,255,0),	  GLT_RGB(0,255,0),		 190,        60,    	128,	DEMO_ECG_WAVE_SPEED },
	{ WAVE_ECG2, STR_WAVE_NAME_ECG_II,	STR_NULL,	FONT_ENG_SMB_AA,	FONT_ENG_SB,	   GLT_RGB(0,255,0),		GLT_RGB(0,255,0),	  GLT_RGB(0,255,0),      190/*240*/, 60/*10*/,	128,	DEMO_ECG_WAVE_SPEED },
	{ WAVE_ECG3, STR_WAVE_NAME_ECG_III,	STR_NULL,	FONT_ENG_SMB_AA,	FONT_ENG_SB,	   GLT_RGB(0,255,0),		GLT_RGB(0,255,0),	  GLT_RGB(0,255,0),      190,        60,    	128,	DEMO_ECG_WAVE_SPEED },
	{ WAVE_ECG4, STR_WAVE_NAME_ECG_AVR,	STR_NULL,	FONT_ENG_SMB_AA,	FONT_ENG_SB,	   GLT_RGB(0,255,0),		GLT_RGB(0,255,0),	  GLT_RGB(0,255,0),      190,        60,    	128,	DEMO_ECG_WAVE_SPEED },
	{ WAVE_ECG5, STR_WAVE_NAME_ECG_AVL,	STR_NULL,	FONT_ENG_SMB_AA,	FONT_ENG_SB,	   GLT_RGB(0,255,0),		GLT_RGB(0,255,0),	  GLT_RGB(0,255,0),      190,        60,    	128,	DEMO_ECG_WAVE_SPEED },
	{ WAVE_ECG6, STR_WAVE_NAME_ECG_AVF,	STR_NULL,	FONT_ENG_SMB_AA,	FONT_ENG_SB,	   GLT_RGB(0,255,0),		GLT_RGB(0,255,0),	  GLT_RGB(0,255,0),      190,        60,    	128,	DEMO_ECG_WAVE_SPEED },
	{ WAVE_ECG7, STR_WAVE_NAME_ECG_V,	STR_NULL,	FONT_ENG_SMB_AA,	FONT_ENG_SB,	   GLT_RGB(0,255,0),		GLT_RGB(0,255,0),	  GLT_RGB(0,255,0),      190,        60,    	128,	DEMO_ECG_WAVE_SPEED },
	{ WAVE_SPO2, STR_WAVE_NAME_SPO2,    STR_NULL,	FONT_ENG_SMB_AA,	FONT_ENG_SB,	   GLT_RGB(41,189,189),		GLT_RGB(131,129,131), GLT_RGB(41,189,189),   128,        0, 		64,		DEMO_SPO2_WAVE_SPEED},
	{ WAVE_RESP, STR_WAVE_NAME_RESP,    STR_NULL,	FONT_ENG_SMB_AA,	FONT_ENG_SB,	   GLT_RGB(255,255,0),		GLT_RGB(255,255,0),	  GLT_RGB(255,255,0),    255,        0,    		128,	DEMO_RESP_WAVE_SPEED}
};

c_wave_manage::c_wave_manage()
{
	memset(m_wave_ctrls, 0, sizeof(m_wave_ctrls));
}

int c_wave_manage::register_wave_ctrl(WAVE_TYPE wave_type, c_wave_ctrl* p_wave)
{
	if (NULL == p_wave)
	{
		ASSERT(FALSE);
		return -1;
	}

	int i = 0;
	while(m_wave_ctrls[wave_type][i] && i < WAVE_CTRL_MAX)
	{
		if(m_wave_ctrls[wave_type][i++] == p_wave)
		{//repeat register
			ASSERT(FALSE);
			return 0;
		}
	}

	WAVE_CTRL_DISCPRITOR* p_disp = s_demo_wave_ctrl_discpritor;

	p_wave->set_max_min_base(p_disp[wave_type].max_data,p_disp[wave_type].min_data,
							p_disp[wave_type].pivot_data);
	p_wave->set_wave_name(p_disp[wave_type].wave_name);
	p_wave->set_wave_unit(p_disp[wave_type].wave_unit);
	p_wave->set_wave_name_font_type(p_disp[wave_type].wave_name_font_type());
	p_wave->set_wave_unit_font_type(p_disp[wave_type].wave_unit_font_type());
	p_wave->set_wave_name_color(p_disp[wave_type].wave_name_color);
	p_wave->set_wave_unit_color(p_disp[wave_type].wave_unit_color);
	p_wave->set_wave_color(p_disp[wave_type].wave_color);
	p_wave->set_wave_sample_rate(p_disp[wave_type].sample_rate);
	p_wave->set_wave(&m_waves[p_disp[wave_type].wave_id]);
	i = 0;
	while(i < WAVE_CTRL_MAX)
	{
		if(!m_wave_ctrls[wave_type][i])
		{
			m_wave_ctrls[wave_type][i++] = p_wave;
			break;
		}
		i++;
	}
	return 1;
}

int c_wave_manage::save_curve_data(WAVE_TYPE wave_type, short data)
{
	if(wave_type >= WAVE_TYPE_MAX)
	{
		ASSERT(FALSE);
	}
	m_waves[wave_type].write_wave_data(data);
	return 0;
}

void c_wave_manage::refurbish_all_curve()
{
	static unsigned char s_frame_num;
	s_frame_num++;

	int i;
	for (i = 0; i < WAVE_TYPE_MAX; i++)
	{//for speed up the routine, I skip a complete checking.
		if (m_wave_ctrls[i][0] && m_wave_ctrls[i][0]->is_visible() &&
		   (m_wave_ctrls[i][0]->is_data_enough() == false))
		{
			return;
		}
	}

	for (i = 0; i < WAVE_TYPE_MAX; i++)
	{
		int j = 0;
		while(m_wave_ctrls[i][j] && m_wave_ctrls[i][j]->is_visible() && j < WAVE_CTRL_MAX)
		{
			m_wave_ctrls[i][j++]->refresh_wave(s_frame_num);
		}
	}
}

void c_wave_manage::clean_all_wave(bool redraw)
{
	for (int i = 0; i < WAVE_TYPE_MAX; i++)
	{
		int j = 0;
		while (m_wave_ctrls[i][j] && j < WAVE_CTRL_MAX)
		{
			m_wave_ctrls[i][j]->clear_data();
			if (redraw == TRUE)
			{
				m_wave_ctrls[i][j]->clear_wave();
				m_wave_ctrls[i][j]->on_paint();
				j++;
			}
		}
	}
}
