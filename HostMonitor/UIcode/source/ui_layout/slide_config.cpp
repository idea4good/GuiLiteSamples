#include "../include/GuiLite.h"
#include "../include/define.h"
#include "../include/ctrl_id.h"

#include "Dialog/patient_setup/patient_setup_dlg.h"
#include "Dialog/patient_setup/patient_setup_dlg_xml.h"
#include "Dialog/about/about_dlg.h"
#include "Dialog/about/about_dlg_xml.h"

class c_config_root : public c_wnd {
	virtual void on_init_children()
	{
		((c_button*)get_wnd_ptr(ID_SETUP_BUTTON))->set_on_click((WND_CALLBACK)&c_config_root::on_clicked);
		((c_button*)get_wnd_ptr(ID_ABOUT_BUTTON))->set_on_click((WND_CALLBACK)&c_config_root::on_clicked);
	}
	void on_clicked(int ctrl_id, int param)
	{
		switch (ctrl_id)
		{
		case ID_SETUP_BUTTON:
			c_dialog::open_dialog((c_dialog*)get_wnd_ptr(ID_SETUP_DLG), false);
			break;
		case ID_ABOUT_BUTTON:
			c_dialog::open_dialog((c_dialog*)get_wnd_ptr(IDD_ABOUT_DLG), false);
			break;
		default:
			ASSERT(false);
			break;
		}
	}
};

//////////////////////////////////////////////////////////////////////////

#define PAGE_WIDTH		(UI_WIDTH * 2 / 3)
#define PAGE_HEIGHT		(UI_HEIGHT - TOP_BAR_HEIGHT)
#define BUTTON_WIDTH	180
#define BUTTON_HEIGHT	40
#define DIALOG_Y		(BUTTON_HEIGHT + 10)
#define DIALOG_HEIGHT	(PAGE_HEIGHT - DIALOG_Y)

static c_config_root s_root;
static c_button s_btn_patient_setup;
static c_button s_btn_demo_setup;
static c_patient_setup_dlg s_patient_setup_dlg;
static c_about_dlg s_about;

static WND_TREE s_config_children[]=
{
	{&s_btn_patient_setup,	ID_SETUP_BUTTON, "Patient Setup",		0,						5,	BUTTON_WIDTH, BUTTON_HEIGHT},
	{&s_btn_demo_setup,		ID_ABOUT_BUTTON, "About",				(BUTTON_WIDTH + 10),	5,	BUTTON_WIDTH, BUTTON_HEIGHT},

	{&s_patient_setup_dlg,	ID_SETUP_DLG, "Patient Setup",		0,	DIALOG_Y,	PAGE_WIDTH, DIALOG_HEIGHT, g_patient_setup_children},
	{&s_about,				IDD_ABOUT_DLG, "About",				0,	DIALOG_Y,	PAGE_WIDTH, DIALOG_HEIGHT, g_about_children},
	{0,0,0,0,0,0,0}
};

void create_page_config(c_slide_group* group)
{
	group->add_slide(&s_root, ID_PAGE_CONFIG, 0, 0, PAGE_WIDTH, PAGE_HEIGHT, s_config_children,Z_ORDER_LEVEL_2);
}
