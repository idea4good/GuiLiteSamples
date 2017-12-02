#include "core_include/api.h"
#include "core_include/rect.h"
#include "core_include/cmd_target.h"
#include "core_include/wnd.h"
#include "gui_include/button.h"
#include "gui_include/spinbox.h"
#include "gui_include/label.h"
#include "gui_include/list_box.h"
#include "gui_include/edit.h"
#include "../include/ctrl_id.h"
#include "../include/define.h"
#include "../source/resource/font/strings.h"
#include "patient_setup_dlg_xml.h"

#define DLG_YMD_EDIT_WIDTH			( ( DLG_CTRL_WIDTH + 80 ) / 3 )
#define DLG_YEAR_EDIT_X				( DLG_RIGHT_CTRL_X - 90 )
#define DLG_MONTH_EDIT_X			( DLG_YEAR_EDIT_X + 5 + DLG_YMD_EDIT_WIDTH )
#define DLG_DAY_EDIT_X				( DLG_YEAR_EDIT_X + 10 + DLG_YMD_EDIT_WIDTH * 2 )


static c_label s_label_first_name;
static c_label s_label_second_name;
static c_label s_label_sick_type;
static c_label s_label_sex;
static c_label s_label_height;
static c_label s_label_weight;
static c_label s_label_birthday;
static c_label s_label_case;
static c_label s_label_admission_date;
static c_label s_label_blood_type;

static c_edit s_edit_surname;
static c_edit s_edit_name;
static c_list_box s_lb_sick_type;
static c_list_box s_lb_sex;
static c_edit s_edit_height;
static c_edit s_edit_weight;
static c_spin_box s_sb_birthday_y;
static c_spin_box s_sb_birthday_m;
static c_spin_box s_sb_birthday_d;
static c_edit s_edit_case;
static c_spin_box s_sb_admission_y;
static c_spin_box s_sb_admission_m;
static c_spin_box s_sb_admission_d;
static c_list_box s_lb_blood_type;

WND_TREE g_patient_setup_children[]=
{
	{&s_label_first_name,	1,	STR_SETUP_DLG_SURNAME,  DLG_LEFT_CTRL_X, DLG_CTRL_Y(0), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_second_name,	2, 	STR_SETUP_DLG_NAME,		DLG_LEFT_CTRL_X, DLG_CTRL_Y(1), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_case,			3,  STR_SETUP_DLG_CASE,     DLG_LEFT_CTRL_X, DLG_CTRL_Y(2), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_sex,			4,  STR_SEX,                DLG_LEFT_CTRL_X, DLG_CTRL_Y(3), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_sick_type,	5,  STR_PATIENT_TYPE,       DLG_LEFT_CTRL_X, DLG_CTRL_Y(4), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_height,		6,  STR_STATURE,            DLG_LEFT_CTRL_X, DLG_CTRL_Y(5), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_weight,		7,  STR_AVOIRDUPOIS,        DLG_LEFT_CTRL_X, DLG_CTRL_Y(6), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_blood_type,	8,  STR_SETUP_DLG_BLOOD,    DLG_LEFT_CTRL_X, DLG_CTRL_Y(7), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_admission_date,9,  STR_SETUP_DLG_ADMIT_DATE,DLG_LEFT_CTRL_X,DLG_CTRL_Y(8),DLG_CTRL_WIDTH - 80,DLG_CTRL_HEIGHT},
	{&s_label_birthday,		10, STR_BIRTHDAY,           DLG_LEFT_CTRL_X, DLG_CTRL_Y(9), DLG_CTRL_WIDTH - 80,DLG_CTRL_HEIGHT},
	
	{&s_edit_surname,	ID_SETUP_DLG_EDIT_FIRST_NAME,	NULL, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(0), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_edit_name,		ID_SETUP_DLG_EDIT_SECOND_NAME,	NULL, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(1), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_edit_case,      ID_SETUP_DLG_EDIT_CASE,         NULL, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(2), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},	
	{&s_lb_sex,         ID_SETUP_DLG_LB_SEX,			NULL, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(3), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_lb_sick_type,   ID_SETUP_DLG_LB_PATIENT_TYPE,	NULL, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(4), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_edit_height,    ID_SETUP_DLG_EDIT_HEIGHT,		NULL, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(5), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_edit_weight,	ID_SETUP_DLG_EDIT_WEIGHT,		NULL, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(6), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_lb_blood_type,  ID_SETUP_DLG_LB_BLOOD_TYPE,		NULL, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(7), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_sb_admission_y, ID_SETUP_DLG_SB_ADMISSION_YEAR, NULL, DLG_YEAR_EDIT_X,  DLG_CTRL_Y(8), DLG_YMD_EDIT_WIDTH, DLG_CTRL_HEIGHT},
	{&s_sb_admission_m, ID_SETUP_DLG_SB_ADMISSION_MONTH,NULL, DLG_MONTH_EDIT_X, DLG_CTRL_Y(8), DLG_YMD_EDIT_WIDTH, DLG_CTRL_HEIGHT},
	{&s_sb_admission_d, ID_SETUP_DLG_SB_ADMISSION_DAY,  NULL, DLG_DAY_EDIT_X,	DLG_CTRL_Y(8), DLG_YMD_EDIT_WIDTH, DLG_CTRL_HEIGHT},
	{&s_sb_birthday_y,  ID_SETUP_DLG_SB_BIRTHDAY_YEAR,  NULL, DLG_YEAR_EDIT_X,	DLG_CTRL_Y(9), DLG_YMD_EDIT_WIDTH, DLG_CTRL_HEIGHT},
	{&s_sb_birthday_m,  ID_SETUP_DLG_SB_BIRTHDAY_MONTH, NULL, DLG_MONTH_EDIT_X, DLG_CTRL_Y(9), DLG_YMD_EDIT_WIDTH, DLG_CTRL_HEIGHT},
	{&s_sb_birthday_d,  ID_SETUP_DLG_SB_BIRTHDAY_DAY,   NULL, DLG_DAY_EDIT_X,	DLG_CTRL_Y(9), DLG_YMD_EDIT_WIDTH, DLG_CTRL_HEIGHT},
	{NULL,0,0,0,0,0,0}
};
