#include "../include/GuiLite.h"
#include "../source/ui_ctrl_ex/wave_ctrl_ex.h"
#include "../include/ctrl_id.h"

static c_bitmap_wave_ctrl s_spo2wavectrl;
WND_TREE g_spo2_wave_view_children[] = 
{
	{&s_spo2wavectrl, ID_MAIN_SCREEN_SPO2_WAVE_CTRL, 0, 3, 5, 673, 159},
	{0,0,0,0,0,0,0}
};
