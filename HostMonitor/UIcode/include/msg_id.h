#ifndef _KEY_MSG_H
#define _KEY_MSG_H

typedef struct
{
	unsigned int dwMsgId;
	unsigned int dwParam1;
	unsigned int dwParam2;
}MSG_INFO;

typedef enum e_app_msg
{
	USR_MSG_UPDATE_TIME = 0x5300,
	USR_MSG_UPDATE_TREND_VIEW
}E_APP_MSG;

#endif
