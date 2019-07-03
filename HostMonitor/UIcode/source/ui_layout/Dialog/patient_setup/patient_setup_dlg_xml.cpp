#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../widgets_include/button.h"
#include "../widgets_include/spinbox.h"
#include "../widgets_include/label.h"
#include "../widgets_include/list_box.h"
#include "../widgets_include/keyboard.h"
#include "../widgets_include/edit.h"
#include "../include/ctrl_id.h"
#include "../include/define.h"
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
	{&s_label_first_name,	1,	"SurName/姓",		DLG_LEFT_CTRL_X, DLG_CTRL_Y(0), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_second_name,	2, 	"Name/名稱",			DLG_LEFT_CTRL_X, DLG_CTRL_Y(1), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_case,			3,  "Case/番号",			DLG_LEFT_CTRL_X, DLG_CTRL_Y(2), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_sex,			4,  "Gender/성",       DLG_LEFT_CTRL_X, DLG_CTRL_Y(3), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_sick_type,	5,  "Patient Cat./Төрөл", DLG_LEFT_CTRL_X, DLG_CTRL_Y(4), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_height,		6,  "Height/ความสูง",       DLG_LEFT_CTRL_X, DLG_CTRL_Y(5), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_weight,		7,  "Weight/Βάρος",		DLG_LEFT_CTRL_X, DLG_CTRL_Y(6), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_blood_type,	8,  "Blood Type/Тип крови",   DLG_LEFT_CTRL_X, DLG_CTRL_Y(7), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_label_admission_date,9, "Admit date/प्रवेश की तारीख",	DLG_LEFT_CTRL_X,DLG_CTRL_Y(8),DLG_CTRL_WIDTH - 80,DLG_CTRL_HEIGHT},
	{&s_label_birthday,		10, "Birthday/lā hānau",     DLG_LEFT_CTRL_X, DLG_CTRL_Y(9), DLG_CTRL_WIDTH - 80,DLG_CTRL_HEIGHT},
	
	{&s_edit_surname,	ID_SETUP_DLG_EDIT_FIRST_NAME,	0, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(0), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_edit_name,		ID_SETUP_DLG_EDIT_SECOND_NAME,	0, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(1), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_edit_case,      ID_SETUP_DLG_EDIT_CASE,         0, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(2), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},	
	{&s_lb_sex,         ID_SETUP_DLG_LB_SEX,			0, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(3), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_lb_sick_type,   ID_SETUP_DLG_LB_PATIENT_TYPE,	0, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(4), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_edit_height,    ID_SETUP_DLG_EDIT_HEIGHT,		0, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(5), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_edit_weight,	ID_SETUP_DLG_EDIT_WEIGHT,		0, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(6), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_lb_blood_type,  ID_SETUP_DLG_LB_BLOOD_TYPE,		0, DLG_RIGHT_CTRL_X, DLG_CTRL_Y(7), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{&s_sb_admission_y, ID_SETUP_DLG_SB_ADMISSION_YEAR, 0, DLG_YEAR_EDIT_X,  DLG_CTRL_Y(8), DLG_YMD_EDIT_WIDTH, DLG_CTRL_HEIGHT},
	{&s_sb_admission_m, ID_SETUP_DLG_SB_ADMISSION_MONTH,0, DLG_MONTH_EDIT_X, DLG_CTRL_Y(8), DLG_YMD_EDIT_WIDTH, DLG_CTRL_HEIGHT},
	{&s_sb_admission_d, ID_SETUP_DLG_SB_ADMISSION_DAY,  0, DLG_DAY_EDIT_X,	DLG_CTRL_Y(8), DLG_YMD_EDIT_WIDTH, DLG_CTRL_HEIGHT},
	{&s_sb_birthday_y,  ID_SETUP_DLG_SB_BIRTHDAY_YEAR,  0, DLG_YEAR_EDIT_X,	DLG_CTRL_Y(9), DLG_YMD_EDIT_WIDTH, DLG_CTRL_HEIGHT},
	{&s_sb_birthday_m,  ID_SETUP_DLG_SB_BIRTHDAY_MONTH, 0, DLG_MONTH_EDIT_X, DLG_CTRL_Y(9), DLG_YMD_EDIT_WIDTH, DLG_CTRL_HEIGHT},
	{&s_sb_birthday_d,  ID_SETUP_DLG_SB_BIRTHDAY_DAY,   0, DLG_DAY_EDIT_X,	DLG_CTRL_Y(9), DLG_YMD_EDIT_WIDTH, DLG_CTRL_HEIGHT},
	{0,0,0,0,0,0,0}
};
