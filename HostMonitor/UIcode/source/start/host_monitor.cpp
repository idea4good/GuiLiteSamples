#include "../core_include/api.h"
#include "../core_include/rect.h"
#include "../core_include/cmd_target.h"
#include "../core_include/wnd.h"
#include "../core_include/resource.h"
#include "../core_include/word.h"
#include "../core_include/surface.h"
#include "../core_include/display.h"

#include "../include/msg_id.h"

#include "../manager/value_manager.h"
#include "../manager/wave_manager.h"
#include "../modules/module_group.h"
#include "../data/database.h"
#include <string.h>
#include <stdlib.h>

extern void load_ui_single(void* phy_fb, int width, int height, int color_bytes);
extern void load_ui_multi(void* phy_fb, int width, int height, int color_bytes);
extern void load_mini_ui_single(void* phy_fb, int width, int height, int color_bytes);
extern void load_mini_ui_multi(void* phy_fb, int width, int height, int color_bytes);

static void init(int display_cnt);
static void real_timer_routine(void* arg);
static void database_timer_callback(void* ptmr, void* parg);

static c_fifo	s_usr_fifo;
int read_usr_msg(MSG_INFO* msg)
{
	return s_usr_fifo.read(msg, sizeof(MSG_INFO));
}

int write_usr_msg(MSG_INFO* msg)
{
	if (msg->dwMsgId & 0xf000000)ASSERT(false);
	return s_usr_fifo.write(msg, sizeof(MSG_INFO));
}

int run(void** main_fbs, int main_cnt, int main_width, int main_height, void** sub_fbs, int sub_cnt, int sub_width, int sub_height, int color_bytes)
{
	init(main_cnt + sub_cnt);

	//Load UI.
	for (int i = 0; i < main_cnt; i++)
	{
		if (0 == i)
		{
			load_ui_single(main_fbs[i], main_width, main_height, color_bytes);
			continue;
		}
		load_ui_multi(main_fbs[i], main_width, main_height, color_bytes);
	}
	for (int i = 0; i < sub_cnt; i++)
	{
		if (0 == i)
		{
			load_mini_ui_single(sub_fbs[i], sub_width, sub_height, color_bytes);
			continue;
		}
		load_mini_ui_multi(sub_fbs[i], sub_width, sub_height, color_bytes);
	}

	//Start system.
	start_real_timer(real_timer_routine);
	register_timer((60 * 1000), database_timer_callback);//update data per minute.

	MSG_INFO msg;
	msg.dwMsgId = USR_MSG_UPDATE_TREND_VIEW;
	write_usr_msg(&msg);

	while(1)
	{
		if (read_usr_msg(&msg) > 0)
		{
			ASSERT((msg.dwMsgId & 0xf0000000) == 0);
			c_cmd_target::handle_usr_msg(msg.dwMsgId, msg.dwParam1, msg.dwParam2);
		}
	}
	return 0;
}

int run(int main_cnt, int main_width, int main_height, int sub_cnt, int sub_width, int sub_height, int color_bytes)
{
	void** main_fbs = (void**)malloc(sizeof(void*) * main_cnt);
	void** sub_fbs = (void**)malloc(sizeof(void*) * sub_cnt);
	for (int i = 0; i < main_cnt; i++)
	{
		main_fbs[i] = calloc(main_width * main_height, color_bytes);
	}
	for (int i = 0; i < sub_cnt; i++)
	{
		sub_fbs[i] = calloc(sub_width * sub_height, color_bytes);
	}
	return run(main_fbs, main_cnt, main_width, main_height, sub_fbs, sub_cnt, sub_width, sub_height, color_bytes);
}

extern void load_theme(int index);
static void init(int display_cnt)
{
	c_database::get_instance()->init();
	load_theme(0);
}

static void real_timer_routine(void* arg)
{
	on_receive_data(0, 0);
	c_wave_manage::get_instance()->refurbish_all_waves();
}

typedef int(*SYNC_DATA)(int hr, int spo2, int rr, int nibp_sys, int nibp_dia, int nibp_mean);
extern SYNC_DATA gSyncData;
static void database_timer_callback(void* ptmr, void* parg)
{
	VALUE_SET data;
	memset(&data, 0, sizeof(data));
	c_value_manager* real_data_mgr = c_value_manager::get_instance();

	data.time = get_time_in_second();
	data.hr = data.pr = real_data_mgr->get_value(VALUE_HR);
	data.spo2 = real_data_mgr->get_value(VALUE_SPO2);
	data.rr = real_data_mgr->get_value(VALUE_RESP);
	data.nibp_sys = real_data_mgr->get_value(VALUE_NIBP_SYS);
	data.nibp_dia = real_data_mgr->get_value(VALUE_NIBP_DIA);
	data.nibp_mean = real_data_mgr->get_value(VALUE_NIBP_MEAN);
	c_database::get_instance()->write(data);

	MSG_INFO msg;
	msg.dwMsgId = USR_MSG_UPDATE_TREND_VIEW;
	write_usr_msg(&msg);

	if(gSyncData)
	{
		gSyncData(data.hr, data.spo2, data.rr, data.nibp_sys, data.nibp_dia, data.nibp_mean);
	}
}
