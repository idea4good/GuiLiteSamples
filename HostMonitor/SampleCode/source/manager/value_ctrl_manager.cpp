#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../source/manager/value_manager.h"
#include "../ui_ctrl_ex/value_ctrl.h"
#include "../include/ctrl_id.h"
#include "value_ctrl_manager.h"

static VALUE_CTRL_XML s_all_value_ctrl_xml[] =
{	/*name*/	/*unit*/	/*value_id*/	/*name_font_type*//*unit_font_type*//*limit_font_type*//*value_font_type*/ 	/*name_color*/		/*unit_color*/		/*limit_color*/

	{ "HR",		"BPM",		VALUE_HR,		FONT_ENG_SMB,	FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_LLLB,		GL_RGB(0,255,0),	GL_RGB(0,255,0),		GL_RGB(0,255,0)},
	{ "PVCs",	NULL,		VALUE_PVCs,		FONT_ENG_SB,	FONT_ENG_SB,		FONT_NULL,			FONT_ENG_MB,		GL_RGB(0,255,0),	GL_RGB(0,255,0),		GL_RGB(0,255,0)},
	{ "II",		NULL,	    VALUE_ST_II,    FONT_ENG_SB,	FONT_ENG_SB,		FONT_NULL,			FONT_ENG_MB,		GL_RGB(0,255,0),	GL_RGB(131,129,131),	GL_RGB(0,255,0)},

	{ "SPO2",	"%",		VALUE_SPO2,		FONT_ENG_SMB,	FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_LLLB,		GL_RGB(41,189,189),GL_RGB(41,189,189),	GL_RGB(41,189,189)},
	{ "PR",		NULL,		VALUE_PR,		FONT_ENG_SB,	FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_LLB,	    GL_RGB(41,189,189),GL_RGB(41,189,189),	GL_RGB(41,189,189)},

	{ "RESP",	NULL,       VALUE_RESP,		FONT_ENG_SMB,	FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_LLLB,		GL_RGB(255,255,0),	GL_RGB(255,255,0),		GL_RGB(255,255,0)},

	{ "T1",	   "C",			VALUE_TEMP_T1,	FONT_ENG_SMB,	FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_MB,		GL_RGB(255,255,255),GL_RGB(255,255,255),	GL_RGB(255,255,255)},
	{ "T2",	   "C",			VALUE_TEMP_T2,	FONT_ENG_SMB,	FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_MB,		GL_RGB(255,255,255),GL_RGB(255,255,255),	GL_RGB(255,255,255)},
	{ "TD",	   "C",			VALUE_TEMP_TD,	FONT_ENG_SMB,	FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_MB,	    GL_RGB(255,255,255),GL_RGB(255,255,255),	GL_RGB(255,255,255)},
	
	{	NULL,	"mmHg",     VALUE_NIBP_SYS,	FONT_ENG_SMB,	FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_MB,		GL_RGB(255,255,255),GL_RGB(255,255,255),	GL_RGB(255,255,255)},
	{	NULL,	NULL,       VALUE_NIBP_DIA,	FONT_ENG_SMB,	FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_MB,		GL_RGB(255,255,255),GL_RGB(255,255,255),	GL_RGB(255,255,255)},
	{	NULL,	NULL,		VALUE_NIBP_MEAN,FONT_ENG_SMB,	FONT_ENG_SB,		FONT_ENG_SMB,		FONT_ENG_MB,		GL_RGB(255,255,255),GL_RGB(255,255,255),	GL_RGB(255,255,255)},
	
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
			p_value_ctrl->set_name(p_cur_disc->name);
			p_value_ctrl->set_unit_str(p_cur_disc->unit);
			p_value_ctrl->set_value_id(p_cur_disc->value_id);

			p_value_ctrl->set_high_limit(200, 0);
			p_value_ctrl->set_low_limit(0, 0);

			p_value_ctrl->set_name_font_type(c_my_resource::get_font(p_cur_disc->name_font_type));
			p_value_ctrl->set_unit_font_type(c_my_resource::get_font(p_cur_disc->unit_font_type));
			p_value_ctrl->set_limit_font_type(c_my_resource::get_font(p_cur_disc->limit_font_type));
			p_value_ctrl->set_value_font_type(c_my_resource::get_font(p_cur_disc->value_font_type));
			
			p_value_ctrl->set_name_color(p_cur_disc->name_color);
			p_value_ctrl->set_unit_color(p_cur_disc->unit_color);
			p_value_ctrl->set_limit_color(p_cur_disc->limit_color);
			break;
		}
		p_cur_disc ++;
	}
}
