#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "../source/manager/value_manager.h"
#include "../ui_ctrl_ex/value_ctrl.h"
#include "../source/resource/font/strings.h"
#include "gui_include/font.h"
#include "../include/ctrl_id.h"
#include "value_ctrl_manager.h"

static VALUE_CTRL_XML s_all_value_ctrl_xml[] =
{		/*name_id*/			/*unit_id*/			/*value_id*/	/*name_font_type*//*unit_font_type*//*limit_font_type*//*value_font_type*/   /*value_big_font_type*/ 	/*name_color*/		/*unit_color*/		/*limit_color*/

	{	STR_HR,		       STR_UNIT_BPM,		VALUE_HR,		FONT_ENG_SMB_AA, FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_MB,	    FONT_ENG_LLLLB,     	GLT_RGB(0,255,0),	GLT_RGB(0,255,0),		GLT_RGB(0,255,0)},
	{	STR_PVCs,	       STR_NULL,			VALUE_PVCs,		FONT_ENG_SB,	 FONT_ENG_S,		FONT_ENG_S,			FONT_ENG_MB_AA,		FONT_ENG_LLB,         	GLT_RGB(0,255,0),	GLT_RGB(0,255,0),		GLT_RGB(0,255,0)},
	{	STR_ECG_LEAD_I,	   STR_NULL,	        VALUE_ST_I, 	FONT_ENG_SB,	 FONT_ENG_S,		FONT_ENG_S,			FONT_ENG_SB,		FONT_ENG_LLB,        	GLT_RGB(0,255,0),	GLT_RGB(131,129,131),	GLT_RGB(0,255,0)},
	{	STR_ECG_LEAD_II,   STR_NULL,	        VALUE_ST_II,    FONT_ENG_SB,	 FONT_ENG_S,		FONT_ENG_S,			FONT_ENG_SB,		FONT_ENG_LLB,         	GLT_RGB(0,255,0),	GLT_RGB(131,129,131),	GLT_RGB(0,255,0)},
	{	STR_ECG_LEAD_III,  STR_NULL,	        VALUE_ST_III,	FONT_ENG_SB,	 FONT_ENG_S,		FONT_ENG_S,			FONT_ENG_SB,		FONT_ENG_LLB,        	GLT_RGB(0,255,0),	GLT_RGB(131,129,131),	GLT_RGB(0,255,0)},

	{	STR_ECG_LEAD_AVR,	STR_NULL,           VALUE_ST_AVR,	FONT_ENG_SB,	 FONT_ENG_S,		FONT_ENG_S,			FONT_ENG_SB,		FONT_ENG_LLB,     	    GLT_RGB(0,255,0),	GLT_RGB(131,129,131),	GLT_RGB(0,255,0)},
	{	STR_ECG_LEAD_AVL,	STR_NULL,			VALUE_ST_AVL,	FONT_ENG_SB,	 FONT_ENG_S,		FONT_ENG_S,			FONT_ENG_SB,		FONT_ENG_LLB,        	GLT_RGB(0,255,0),	GLT_RGB(131,129,131),	GLT_RGB(0,255,0)},
	{	STR_ECG_LEAD_AVF,	STR_NULL,	        VALUE_ST_AVF,	FONT_ENG_SB,	 FONT_ENG_S,		FONT_ENG_S,			FONT_ENG_SB,		FONT_ENG_LLB,     	    GLT_RGB(0,255,0),	GLT_RGB(131,129,131),	GLT_RGB(0,255,0)},
	{	STR_ECG_LEAD_V,		STR_NULL,	        VALUE_ST_V1,	FONT_ENG_SB,	 FONT_ENG_S,		FONT_ENG_S,			FONT_ENG_SB,		FONT_ENG_LLB,     	    GLT_RGB(0,255,0),	GLT_RGB(131,129,131),	GLT_RGB(0,255,0)},
	
	{	STR_SPO2,	       STR_UNIT_PERCENTAGE, VALUE_SPO2,		FONT_ENG_SMB_AA, FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_MB,		FONT_ENG_LLLLB,     	GLT_RGB(41,189,189),GLT_RGB(41,189,189),	GLT_RGB(41,189,189)},
	{	STR_PR,		       STR_NULL,			VALUE_PR,		FONT_ENG_SB,	 FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_SMB_AA,	FONT_ENG_LLB,        	GLT_RGB(41,189,189),GLT_RGB(41,189,189),	GLT_RGB(41,189,189)},

	{	STR_RESP,	       STR_NULL,            VALUE_RESP,		FONT_ENG_SMB_AA, FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_MB,		FONT_ENG_LLLLB,     	GLT_RGB(255,255,0),	GLT_RGB(255,255,0),		GLT_RGB(255,255,0)},

	{	STR_TEMP_T1,	   STR_UNIT_TEMP_C,     VALUE_TEMP_T1,	FONT_ENG_SMB_AA, FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_MB,		FONT_ENG_LLLLB,       	GLT_RGB(255,255,255),GLT_RGB(255,255,255),	GLT_RGB(255,255,255)},
	{	STR_TEMP_T2,	   STR_UNIT_TEMP_C,     VALUE_TEMP_T2,	FONT_ENG_SMB_AA, FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_MB,		FONT_ENG_LLB,       	GLT_RGB(255,255,255),GLT_RGB(255,255,255),	GLT_RGB(255,255,255)},
	{	STR_TEMP_TD,	   STR_UNIT_TEMP_C,     VALUE_TEMP_TD,	FONT_ENG_SMB_AA, FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_MMB_AA,	FONT_ENG_LLB,     	    GLT_RGB(255,255,255),GLT_RGB(255,255,255),	GLT_RGB(255,255,255)},
	
	{	STR_NULL,	       STR_UNIT_MMHG,       VALUE_NIBP_SYS,	FONT_ENG_SMB_AA, FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_MB,		FONT_ENG_LLB,       	GLT_RGB(255,255,255),GLT_RGB(255,255,255),	GLT_RGB(255,255,255)},
	{	STR_NULL,	       STR_NULL,            VALUE_NIBP_DIA,	FONT_ENG_SMB_AA, FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_MB,		FONT_ENG_LLB,       	GLT_RGB(255,255,255),GLT_RGB(255,255,255),	GLT_RGB(255,255,255)},
	{	STR_NULL,	       STR_NULL,            VALUE_NIBP_MEAN,FONT_ENG_SMB_AA, FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_MB_AA,		FONT_ENG_LLB,       	GLT_RGB(255,255,255),GLT_RGB(255,255,255),	GLT_RGB(255,255,255)},
	
	{	NULL,0,VALUE_MAX}
};

void c_value_ctrl_manage::config_param_ctrl_att(E_VALUE_TYPE value_id, c_value_ctrl* p_value_ctrl)
{
	if (NULL == p_value_ctrl)
	{
		ASSERT(0);
		return;
	}

	VALUE_CTRL_XML* p_cur_disc = s_all_value_ctrl_xml;

	while (p_cur_disc && p_cur_disc->value_id != VALUE_MAX)
	{
		if (p_cur_disc->value_id == value_id)
		{
			p_value_ctrl->set_name(p_cur_disc->name_id);
			p_value_ctrl->set_unit_strid(p_cur_disc->unit_id);
			p_value_ctrl->set_value_id(p_cur_disc->value_id);

			p_value_ctrl->set_high_limit(200, 0);
			p_value_ctrl->set_low_limit(0, 0);

			p_value_ctrl->set_name_font_type(p_cur_disc->name_font_type());
			p_value_ctrl->set_unit_font_type(p_cur_disc->unit_font_type());
			p_value_ctrl->set_limit_font_type(p_cur_disc->limit_font_type());
			
			p_value_ctrl->set_value_font_type(p_cur_disc->value_font_type());
			
			p_value_ctrl->set_name_color(p_cur_disc->name_color);
			p_value_ctrl->set_unit_color(p_cur_disc->unit_color);
			p_value_ctrl->set_limit_color(p_cur_disc->limit_color);
			return;
		}
		p_cur_disc ++;
	}
}
