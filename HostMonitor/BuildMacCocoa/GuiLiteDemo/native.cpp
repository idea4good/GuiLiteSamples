#include "GuiLiteDemo-Bridging-Header.h"

extern int startHostMonitor(int main_cnt, int main_width, int main_height, int sub_cnt, int sub_width, int sub_height, int color_bytes);
extern int sendTouch2HostMonitor(int x, int y, bool is_down, int display_id);
extern void* getUiOfHostMonitor(int display_id, int* width, int* height, bool force_update);

void _startHostMonitor(int width, int height, int colorBytes)
{
    startHostMonitor(1, width, height, 0, 1024, 370, colorBytes);
}

void* _getUiOfHostMonitor()
{
    return getUiOfHostMonitor(0, 0, 0, false);
}

void mouse_down(int x, int y)
{
    sendTouch2HostMonitor(x, y, true, 0);
}

void mouse_up(int x, int y)
{
    sendTouch2HostMonitor(x, y, false, 0);
}
