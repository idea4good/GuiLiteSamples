#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "gui_include/table.h"
#include "../include/ctrl_id.h"
#include "nibp_list_xml.h"

static c_table s_nibp_list_view_table;
WND_TREE g_nibp_list_view_children[] = 
{
	{&s_nibp_list_view_table, ID_NIBP_LIST_VIEW_TABLE, 0, 0, 0, 335, 169},
	{NULL,0,0,0,0,0,0}
};
