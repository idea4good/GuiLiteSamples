#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../core_include/surface.h"
#include "../core_include/display.h"
#include "../widgets_include/label.h"
#include "../widgets_include/button.h"
#include "../widgets_include/dialog.h"
#include "../widgets_include/spinbox.h"
#include "../widgets_include/list_box.h"
#include "../widgets_include/keyboard.h"
#include "../widgets_include/edit.h"
#include "../include/ctrl_id.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "patient_setup_dlg.h"

void c_patient_setup_dlg::on_paint()
{
	c_dialog::on_paint();
    patient_dlg_crtl_init();
}

void c_patient_setup_dlg::patient_dlg_crtl_init(void)
{
	c_list_box  *plbox = (c_list_box*)get_wnd_ptr(ID_SETUP_DLG_LB_SEX);
	plbox->clear_item();
	plbox->add_item("Male");
	plbox->add_item("Female");
    plbox->select_item(1);

	plbox = (c_list_box*)get_wnd_ptr(ID_SETUP_DLG_LB_PATIENT_TYPE);
	plbox->clear_item();
	plbox->add_item("ADU");
	plbox->add_item("PED");
	plbox->add_item("NEO");
    plbox->select_item(1);

	plbox = (c_list_box*)get_wnd_ptr(ID_SETUP_DLG_LB_BLOOD_TYPE);
	plbox->clear_item();
	plbox->add_item("A");
	plbox->add_item("B");
	plbox->add_item("AB");
	plbox->add_item("O");
	plbox->select_item(1);

    //Birthday
	c_spin_box  *psbox_year = (c_spin_box*)get_wnd_ptr(ID_SETUP_DLG_SB_BIRTHDAY_YEAR);
	c_spin_box  *psbox_month = (c_spin_box*)get_wnd_ptr(ID_SETUP_DLG_SB_BIRTHDAY_MONTH);
	c_spin_box  *psbox_day = (c_spin_box*)get_wnd_ptr(ID_SETUP_DLG_SB_BIRTHDAY_DAY);
	if((psbox_year==0) || (psbox_month==0) || (psbox_day==0))
	{
		ASSERT(false);
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
	pEdit->set_keyboard_style(STYLE_ALL_BOARD);
    pEdit->set_text("Gui");

	pEdit = (c_edit*)get_wnd_ptr(ID_SETUP_DLG_EDIT_SECOND_NAME);
	pEdit->set_keyboard_style(STYLE_ALL_BOARD);
	pEdit->set_text("Lite");

	pEdit = (c_edit*)get_wnd_ptr(ID_SETUP_DLG_EDIT_CASE);
	pEdit->set_keyboard_style(STYLE_ALL_BOARD);
    pEdit->set_text("001");

    pEdit = (c_edit*)get_wnd_ptr(ID_SETUP_DLG_EDIT_HEIGHT);
	pEdit->set_keyboard_style(STYLE_NUM_BOARD);
	pEdit->set_text("120");

	pEdit = (c_edit*)get_wnd_ptr(ID_SETUP_DLG_EDIT_WEIGHT);
	pEdit->set_keyboard_style(STYLE_NUM_BOARD);
	pEdit->set_text("150");
}
