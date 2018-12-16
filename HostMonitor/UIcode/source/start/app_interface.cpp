#include "../core_include/api.h"
#include "../core_include/cmd_target.h"
#include "../core_include/msg.h"
#include "../core_include/rect.h"
#include "../core_include/surface.h"
#include "../core_include/display.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern c_display* get_display(int display_id);
extern c_fifo* get_hid_fifo(int display_id);
extern int run(int main_cnt, int main_width, int main_height, int sub_cnt, int sub_width, int sub_height, int color_bytes);
extern int run(void** main_fbs, int main_cnt, int main_width, int main_height, void** sub_fbs, int sub_cnt, int sub_width, int sub_height, int color_bytes);

//Referenced by iOs, Android, Linux, Windows APP.
int startHostMonitor(int main_cnt, int main_width, int main_height, int sub_cnt, int sub_width, int sub_height, int color_bytes)
{
	return run(main_cnt, main_width, main_height, sub_cnt, sub_width, sub_height, color_bytes);
}

int startHostMonitor(void** main_fbs, int main_cnt, int main_width, int main_height, void** sub_fbs, int sub_cnt, int sub_width, int sub_height, int color_bytes)
{
	return run(main_fbs, main_cnt, main_width, main_height, sub_fbs, sub_cnt, sub_width, sub_height, color_bytes);
}

int sendTouch2HostMonitor(void* buf, int len, int display_id)
{
	ASSERT(len == sizeof(MSG_INFO));
	c_fifo* fifo = get_hid_fifo(display_id);
	if (fifo)
	{
		return fifo->write(buf, len);
	}
	return 0;
}

void* getUiOfHostMonitor(int display_id, int* width, int* height, bool force_update)
{
	c_display* display = get_display(display_id);
	if (display)
	{
		return display->get_updated_fb(width, height, force_update);
	}
	return NULL;
}

int captureUiOfHostMonitor(int display_id)
{
	char file_name[32];
	memset(file_name, 0, sizeof(file_name));
	sprintf(file_name, "snapshot_%d.bmp", display_id);

	c_display* display = get_display(display_id);
	if (display)
	{
		return display->snap_shot(file_name);
	}
	return 0;
}

//Cloud API
typedef int(*SYNC_DATA)(int hr, int spo2, int rr, int nibp_sys, int nibp_dia, int nibp_mean);
SYNC_DATA gSyncData;