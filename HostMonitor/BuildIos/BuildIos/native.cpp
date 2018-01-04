#include "native.hpp"

typedef struct {
    unsigned int dwMsgId;
    unsigned int dwParam1;
    unsigned int dwParam2;
}OUTMSGINFO;

extern int run(int main_cnt, int main_width, int main_height,
               int sub_cnt, int sub_width, int sub_height,
               int color_bytes);
extern "C" int send_hid_msg(void* buf, int len, int display_id);

void run_host_monitor()
{
    run(1, 1024, 768, 0, 1024, 370, 2);
}

void mouse_down(int x, int y)
{
    OUTMSGINFO msg;
    msg.dwMsgId = 0x4700;
    msg.dwParam1 = x;
    msg.dwParam2 = y;
    send_hid_msg(&msg, sizeof(msg), 0);
}

void mouse_up(int x, int y)
{
    OUTMSGINFO msg;
    msg.dwMsgId = 0x4600;
    msg.dwParam1 = x;
    msg.dwParam2 = y;
    send_hid_msg(&msg, sizeof(msg), 0);
}
///////////////////////////////
void do_assert(const char* file, int line)
{
    printf("assert! file:%s, line:%d", file, line);
}

void log_out(const char* log)
{
    printf("%s", log);
}
