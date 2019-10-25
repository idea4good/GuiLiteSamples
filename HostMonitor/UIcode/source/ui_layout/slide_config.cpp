#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/api.h"
#include "../core_include/wnd.h"
#include "../core_include/surface.h"
#include "../core_include/display.h"
#include "../widgets_include/button.h"
#include "../widgets_include/dialog.h"
#include "../widgets_include/slide_group.h"

#include "../include/define.h"
#include "../include/ctrl_id.h"

#include "Dialog/patient_setup/patient_setup_dlg.h"
#include "Dialog/patient_setup/patient_setup_dlg_xml.h"
#include "Dialog/about/about_dlg.h"
#include "Dialog/about/about_dlg_xml.h"

class c_config_root : public c_wnd {
	virtual c_wnd* clone(){return new c_config_root();}
	void on_clicked(unsigned int ctrl_id);
	GL_DECLARE_MESSAGE_MAP()
};

GL_BEGIN_MESSAGE_MAP(c_config_root)
ON_GL_BN_CLICKED(5, c_config_root::on_clicked)
ON_GL_BN_CLICKED(7, c_config_root::on_clicked)
GL_END_MESSAGE_MAP()

void c_config_root::on_clicked(unsigned int ctrl_id)
{
	switch(ctrl_id)
	{
	case 5:
		c_dialog::open_dialog((c_dialog*)get_wnd_ptr(IDD_SETUP_DLG), false);
		break;
	case 7:
		c_dialog::open_dialog((c_dialog*)get_wnd_ptr(IDD_ABOUT_DLG), false);
		break;
	default:
		ASSERT(false);
		break;
	}
}

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
	{&s_btn_patient_setup,	5, "Patient Setup",		0,						5,	BUTTON_WIDTH, BUTTON_HEIGHT},
	{&s_btn_demo_setup,		7, "About",				(BUTTON_WIDTH + 10),	5,	BUTTON_WIDTH, BUTTON_HEIGHT},

	{&s_patient_setup_dlg,	IDD_SETUP_DLG, "Patient Setup",		0,	DIALOG_Y,	PAGE_WIDTH, DIALOG_HEIGHT, g_patient_setup_children},
	{&s_about,				IDD_ABOUT_DLG, "About",				0,	DIALOG_Y,	PAGE_WIDTH, DIALOG_HEIGHT, g_about_children},
	{0,0,0,0,0,0,0}
};

void create_page_config(c_slide_group* group)
{
	group->add_slide(&s_root, ID_PAGE_CONFIG, 0, 0, PAGE_WIDTH, PAGE_HEIGHT, s_config_children,Z_ORDER_LEVEL_2);
}

void create_clone_page_config(c_slide_group* group)
{
	group->add_clone_silde(&s_root, ID_PAGE_CONFIG, 0, 0, PAGE_WIDTH, PAGE_HEIGHT, s_config_children, Z_ORDER_LEVEL_2);
}
