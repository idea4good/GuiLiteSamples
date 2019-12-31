#include "BuildIos-Bridging-Header.h"
#include <stdlib.h>

extern void startHostMonitor(void* phy_fb, int screen_width, int screen_height, int color_bytes);
extern void sendTouch2HostMonitor(int x, int y, bool is_down, int display_id);
extern void* getUiOfHostMonitor(int display_id, int* width, int* height, bool force_update);

void _startHostMonitor(int width, int height, int colorBytes)
{
    startHostMonitor(calloc(width * height, colorBytes), width, height, colorBytes);
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
