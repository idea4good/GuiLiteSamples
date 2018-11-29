/*
 * define.h
 *
 */

#ifndef _DEFINE_H_
#define _DEFINE_H_

//Standard UI
#define UI_WIDTH		1024
#define UI_HEIGHT		768
#define TOP_BAR_HEIGHT	44

//Mini UI
#define MINI_UI_WIDTH	UI_WIDTH
#define MINI_UI_HEIGHT	370

//Dialog
#define DLG_LEFT_CTRL_X		100
#define DLG_CTRL_HEIGHT		30
#define DLG_CTRL_WIDTH		230
#define DLG_RIGHT_CTRL_X	(DLG_LEFT_CTRL_X + DLG_CTRL_WIDTH + 20)
#define DLG_CTRL_Y(row)		(34 + row * 11 +  DLG_CTRL_HEIGHT * row)

#endif /* DEFINE_H_ */
