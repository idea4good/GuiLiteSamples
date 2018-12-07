#include "../core_include/api.h"
#include "../core_include/cmd_target.h"
#include "../core_include/msg.h"
#include "../core_include/rect.h"
#include "../core_include/surface.h"
#include "../core_include/display.h"
#include <stdlib.h>
#include <string.h>

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
	if(len != sizeof(MSG_INFO))
	{
		ASSERT(FALSE);
	}
	return c_hid_pipe::write_hid_msg((MSG_INFO*)buf, display_id);
}

void* getUiOfHostMonitor(int display_id, int* width, int* height)
{
	return c_display::get_frame_buffer(display_id, width, height);
}

int captureUiOfHostMonitor(int display)
{
	return c_display::snap_shot(display);
}

//Cloud API
typedef int(*SYNC_DATA)(int hr, int spo2, int rr, int nibp_sys, int nibp_dia, int nibp_mean);
SYNC_DATA gSyncData;