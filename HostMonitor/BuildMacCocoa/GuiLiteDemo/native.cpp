#include "native.hpp"

typedef struct {
    unsigned int dwMsgId;
    unsigned int dwParam1;
    unsigned int dwParam2;
}OUTMSGINFO;

extern int startHostMonitor(int main_cnt, int main_width, int main_height,
               int sub_cnt, int sub_width, int sub_height,
               int color_bytes);
extern int sendTouch2HostMonitor(void* buf, int len, int display_id);
extern void* getUiOfHostMonitor(int display_id, int* width, int* height, bool force_update);

void run_host_monitor()
{
    startHostMonitor(1, 1024, 768, 0, 1024, 370, 2);
}

void* get_frame_buffer(int display_id, int* width, int* height)
{
    return getUiOfHostMonitor(display_id, width, height, false);
}

void mouse_down(int x, int y)
{
    OUTMSGINFO msg;
    msg.dwMsgId = 0x4700;
    msg.dwParam1 = x;
    msg.dwParam2 = y;
    sendTouch2HostMonitor(&msg, sizeof(msg), 0);
}

void mouse_up(int x, int y)
{
    OUTMSGINFO msg;
    msg.dwMsgId = 0x4600;
    msg.dwParam1 = x;
    msg.dwParam2 = y;
    sendTouch2HostMonitor(&msg, sizeof(msg), 0);
}
