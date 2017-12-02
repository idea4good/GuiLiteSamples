#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "gui_include/label.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "../source/ui_ctrl_ex/value_sub_ctrl.h"
#include "../include/ctrl_id.h"
#include "../source/resource/font/strings.h"
#include "ecg_value_xml.h"


static c_value_ctrl		s_value_hr;
static c_value_sub_ctrl s_value_pvcs;
static c_value_sub_ctrl s_value_stii;

static c_label s_heart_bmp;
static c_label s_st_sw;
static c_label s_st_alarm_bmp;

WND_TREE g_ecg_value_view_children[] =
{
	{	&s_value_hr,	ID_ECG_VIEW_HR_VALUE,	0, 8,	5,	199,	125},
	{	&s_value_pvcs,	ID_ECG_VIEW_PVCs_VALUE,	0, 207,	15,	112,	53},
	{	&s_value_stii,	ID_ECG_VIEW_STII_VALUE,	0, 207,	68,	112,	53},
	{	NULL,0,0,0,0,0,0}
};
