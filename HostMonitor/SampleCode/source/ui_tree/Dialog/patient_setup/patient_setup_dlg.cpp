#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "core_include/msg.h"
#include "gui_include/label.h"
#include "gui_include/button.h"
#include "gui_include/dialog.h"
#include "gui_include/spinbox.h"
#include "gui_include/list_box.h"
#include "gui_include/edit.h"
#include "../source/resource/font/strings.h"
#include "../include/ctrl_id.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "patient_setup_dlg.h"

GLT_BEGIN_MESSAGE_MAP(c_patient_setup_dlg)
ON_SPIN_CONFIRM(ID_SETUP_DLG_SB_BIRTHDAY_DAY, c_patient_setup_dlg::on_spinbox_confirm)
GLT_END_MESSAGE_MAP()

void c_patient_setup_dlg::on_init_children(void)
{
	set_divider_lines(11);
}

void c_patient_setup_dlg::on_paint()
{
	c_dialog::on_paint();
    patient_dlg_crtl_init();
}

void c_patient_setup_dlg::patient_dlg_crtl_init(void)
{
	c_list_box  *plbox = (c_list_box*)get_wnd_ptr(ID_SETUP_DLG_LB_SEX);
	plbox->clear_item();
	plbox->add_item(STR_MALE);
	plbox->add_item(STR_FEMALE);
    plbox->select_item(1);

	plbox = (c_list_box*)get_wnd_ptr(ID_SETUP_DLG_LB_PATIENT_TYPE);
	plbox->clear_item();
	plbox->add_item(STR_ADULT);
	plbox->add_item(STR_PEDIA);
	plbox->add_item(STR_NEONATE);
    plbox->select_item(1);

	plbox = (c_list_box*)get_wnd_ptr(ID_SETUP_DLG_LB_BLOOD_TYPE);
	plbox->clear_item();
	plbox->add_item(STR_BLOOD_A);
	plbox->add_item(STR_BLOOD_B);
	plbox->add_item(STR_BLOOD_AB);
	plbox->add_item(STR_BLOOD_O);
	plbox->select_item(1);

    //Birthday
	c_spin_box  *psbox_year = (c_spin_box*)get_wnd_ptr(ID_SETUP_DLG_SB_BIRTHDAY_YEAR);
	c_spin_box  *psbox_month = (c_spin_box*)get_wnd_ptr(ID_SETUP_DLG_SB_BIRTHDAY_MONTH);
	c_spin_box  *psbox_day = (c_spin_box*)get_wnd_ptr(ID_SETUP_DLG_SB_BIRTHDAY_DAY);
	if((psbox_year==NULL) || (psbox_month==NULL) || (psbox_day==NULL))
	{
		ASSERT(FALSE);
		return;
	}

    psbox_year->set_max_min(2030, 1940);
    psbox_year->set_step(1);
	psbox_month->set_max_min(12, 1);
	psbox_month->set_step(1);
	psbox_day->set_max_min(31, 1);
	psbox_day->set_step(1);

	psbox_year->set_value(1999);
	psbox_month->set_value(10);
	psbox_day->set_value(1);

    psbox_year = (c_spin_box*)get_wnd_ptr(ID_SETUP_DLG_SB_ADMISSION_YEAR);
	psbox_month = (c_spin_box*)get_wnd_ptr(ID_SETUP_DLG_SB_ADMISSION_MONTH);
	psbox_day = (c_spin_box*)get_wnd_ptr(ID_SETUP_DLG_SB_ADMISSION_DAY);

	psbox_year->set_max_min(2030, 1940);
	psbox_year->set_step(1);
	psbox_month->set_max_min(12, 1);
	psbox_month->set_step(1);
	psbox_day->set_max_min(31, 1);
	psbox_day->set_step(1);

	psbox_year->set_value(1999);
	psbox_month->set_value(10);
	psbox_day->set_value(1);

	c_edit *pEdit = (c_edit*)get_wnd_ptr(ID_SETUP_DLG_EDIT_FIRST_NAME);
    pEdit->modify_style(KEY_BOARD_STYLE);
    pEdit->set_text("Gui");

	pEdit = (c_edit*)get_wnd_ptr(ID_SETUP_DLG_EDIT_SECOND_NAME);
	pEdit->modify_style(KEY_BOARD_STYLE);
	pEdit->set_text("Lite");

	pEdit = (c_edit*)get_wnd_ptr(ID_SETUP_DLG_EDIT_CASE);
	pEdit->modify_style(KEY_BOARD_STYLE);
    pEdit->set_text("001");

    pEdit = (c_edit*)get_wnd_ptr(ID_SETUP_DLG_EDIT_HEIGHT);
	pEdit->modify_style(NUM_BOARD_STYLE, KEY_BOARD_STYLE);
	pEdit->set_text("120");

	pEdit = (c_edit*)get_wnd_ptr(ID_SETUP_DLG_EDIT_WEIGHT);
	pEdit->modify_style(NUM_BOARD_STYLE, KEY_BOARD_STYLE);
	pEdit->set_text("150");
}

void c_patient_setup_dlg::on_spinbox_confirm(unsigned int ctrl_id)
{//Do your bussiness here.

}