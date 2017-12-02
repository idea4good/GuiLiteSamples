#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "gui_include/label.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "../include/ctrl_id.h"
#include "../source/resource/font/strings.h"
#include "nibp_value_xml.h"

static c_label s_label_name;
static c_value_ctrl s_value_sys;
static c_value_ctrl s_value_dia;
static c_value_ctrl s_value_mean;

WND_TREE g_nibp_value_view_children[] =
{
	{&s_label_name,		ID_NIBP_VIEW,       		STR_NIBP,	8,    		2,    		45,    	22},
	{&s_value_sys,  	ID_NIBP_VIEW_SYS_VALUE,    	0,      	8,    		20,    		144,    88},
	{&s_value_dia,  	ID_NIBP_VIEW_DIA_VALUE,     0,      	152,  		20,  		100, 	88},
	{&s_value_mean, 	ID_NIBP_VIEW_MEAN_VALUE,	0,    		240,   		25,  		80,  	83},
	{NULL,0,0,0,0,0,0}
};
