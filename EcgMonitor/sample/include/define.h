/*
 * define.h
 *
 */

#ifndef _DEFINE_H_
#define _DEFINE_H_

//Standard UI
#define SCREEN_WIDTH		1024
#define SCREEN_HEIGHT		768
#define TOP_BAR_HEIGHT		44

//Mini UI
#define MINI_SCREEN_WIDTH	SCREEN_WIDTH
#define MINI_SCREEN_HEIGHT	370

//Dialog
#define DLG_LEFT_CTRL_X		100
#define DLG_CTRL_HEIGHT		30
#define DLG_CTRL_WIDTH		230
#define DLG_RIGHT_CTRL_X	(DLG_LEFT_CTRL_X + DLG_CTRL_WIDTH + 20)
#define DLG_CTRL_Y(row)		(34 + row * 11 +  DLG_CTRL_HEIGHT * row)

#endif /* DEFINE_H_ */
