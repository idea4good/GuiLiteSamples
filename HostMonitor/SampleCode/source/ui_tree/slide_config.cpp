#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/api.h"
#include "core_include/wnd.h"
#include "core_include/msg.h"
#include "core_include/surface.h"
#include "gui_include/button.h"
#include "gui_include/dialog.h"
#include "gui_include/slide_group.h"

#include "../include/define.h"
#include "../include/ctrl_id.h"

#include "Dialog/patient_setup/patient_setup_dlg.h"
#include "Dialog/patient_setup/patient_setup_dlg_xml.h"
#include "Dialog/about/about_dlg.h"
#include "Dialog/about/about_dlg_xml.h"

#include "../resource/font/strings.h"

class c_config_root : public c_wnd {
	virtual c_wnd* clone(){return new c_config_root();}
	void on_clicked(unsigned int ctrl_id);
	GLT_DECLARE_MESSAGE_MAP()
};

GLT_BEGIN_MESSAGE_MAP(c_config_root)
ON_GLT_BN_CLICKED(5, c_config_root::on_clicked)
ON_GLT_BN_CLICKED(7, c_config_root::on_clicked)
GLT_END_MESSAGE_MAP()

void c_config_root::on_clicked(unsigned int ctrl_id)
{
	switch(ctrl_id)
	{
	case 5:
		c_dialog::open_dialog((c_dialog*)get_wnd_ptr(IDD_SETUP_DLG));
		break;
	case 7:
		c_dialog::open_dialog((c_dialog*)get_wnd_ptr(IDD_ABOUT_DLG));
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////

#define PAGE_WIDTH		(SCREEN_WIDTH * 2 / 3)
#define PAGE_HEIGHT		(SCREEN_HEIGHT - TOP_BAR_HEIGHT)
#define BUTTON_WIDTH	180
#define BUTTON_HEIGHT	40

static c_config_root s_root;
static c_button s_btn_patient_setup;
static c_button s_btn_demo_setup;
static c_patient_setup_dlg s_patient_setup_dlg;
static c_about_dlg s_about;

static WND_TREE s_config_children[]=
{
	{&s_btn_patient_setup,	5, STR_SETUP_DLG_TITLE,	0,						5,	BUTTON_WIDTH, BUTTON_HEIGHT},
	{&s_btn_demo_setup,		7, STR_ABOUT_SOFTWARE,	(BUTTON_WIDTH + 10),	5,	BUTTON_WIDTH, BUTTON_HEIGHT},
	{NULL,0,0,0,0,0,0}
};

#define DIALOG_Y		(BUTTON_HEIGHT + 10)
#define DIALOG_HEIGHT	(PAGE_HEIGHT - DIALOG_Y)

void create_page_config(c_slide_group* group)
{
	group->add_slide(&s_root, ID_PAGE_CONFIG, 0, 0, PAGE_WIDTH, PAGE_HEIGHT, s_config_children,Z_ORDER_LEVEL_2);

	s_patient_setup_dlg.connect(&s_root, IDD_SETUP_DLG,STR_SETUP_DLG_TITLE, 0, DIALOG_Y, PAGE_WIDTH, DIALOG_HEIGHT, g_patient_setup_children);
	s_about.connect(&s_root, IDD_ABOUT_DLG,STR_ABOUT_SOFTWARE, 0, DIALOG_Y, PAGE_WIDTH, DIALOG_HEIGHT,g_about_children);
	c_dialog::open_dialog(&s_patient_setup_dlg);
}

void create_clone_page_config(c_slide_group* group)
{
	group->add_clone_silde(&s_root, ID_PAGE_CONFIG, 0, 0, PAGE_WIDTH, PAGE_HEIGHT, s_config_children, Z_ORDER_LEVEL_2);

	c_config_root* page_config = (c_config_root*)group->get_wnd_ptr(ID_PAGE_CONFIG);

	c_dialog* dlg = (c_dialog*)s_patient_setup_dlg.connect_clone(page_config,IDD_SETUP_DLG,STR_SETUP_DLG_TITLE,0, DIALOG_Y, PAGE_WIDTH, DIALOG_HEIGHT, g_patient_setup_children);
	s_about.connect_clone(page_config, IDD_ABOUT_DLG, STR_ABOUT_SOFTWARE, 0, DIALOG_Y, PAGE_WIDTH, DIALOG_HEIGHT,g_about_children);
	c_dialog::open_dialog(dlg);
}
