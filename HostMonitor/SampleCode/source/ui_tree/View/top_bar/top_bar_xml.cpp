#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "gui_include/label.h"
#include "../include/ctrl_id.h"
#include "../source/ui_ctrl_ex/time_label.h"
#include "../source/ui_ctrl_ex/value_ctrl.h"
#include "patient/patient_view.h"
#include "top_bar_xml.h"

static c_time_label		s_time_label;
static c_patient_view	s_patient_info;
WND_TREE g_top_view_children[] =
{
	{&s_patient_info,	ID_PATIENT_VIEW_ID,	0,	5,	0, 335,	43},
	{&s_time_label,		ID_TOP_BAR_TIME_ID,	0,	899,0, 90,	43},
	{NULL,0,0,0,0,0,0}
};
