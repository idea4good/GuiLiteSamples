#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../widgets_include/label.h"
#include "../include/ctrl_id.h"
#include "../include/define.h"
#include "about_dlg_xml.h"

static c_label s_soft_name;
static c_label s_platform;
static c_label s_work_condition;
static c_label s_copy_right;
static c_label s_author;
static c_label s_email;

WND_TREE g_about_children[]=
{
	{	&s_soft_name,       1, "Software: GuiLite sample",		DLG_LEFT_CTRL_X, DLG_CTRL_Y(0), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{	&s_platform, 		2, "Platform available: Android, Linux, Windows(Hololens/VR)",DLG_LEFT_CTRL_X, DLG_CTRL_Y(1), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{	&s_work_condition,  3, "CPU support: ARM, X86",DLG_LEFT_CTRL_X, DLG_CTRL_Y(2), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{	&s_copy_right,   	4, "Source code: www.github.com/idea4good (Apache lience)",		DLG_LEFT_CTRL_X, DLG_CTRL_Y(3), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{	&s_author, 			5, "Author: idea4good",			DLG_LEFT_CTRL_X, DLG_CTRL_Y(4), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{	&s_email,   		6, "Email: idea4good@outlook.com",			DLG_LEFT_CTRL_X, DLG_CTRL_Y(5), DLG_CTRL_WIDTH, DLG_CTRL_HEIGHT},
	{	0,0,0,0,0,0,0}
};
