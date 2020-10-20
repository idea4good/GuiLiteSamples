#define GUILITE_ON  //Do not define this macro once more!!!
#include "../manager/wave_manager.h"
#include "../modules/module_group.h"
#include "../data/database.h"
#include "../include/GuiLite.h"
#include <string.h>
#include <stdlib.h>

extern void load_theme(int index);
extern void load_ui_single(void* phy_fb, int width, int height, int color_bytes);

static void init()
{
	c_database::get_instance()->init();
	load_theme(0);
}

static void wave_refresh_timer_callback(void* arg)
{
	on_receive_data(0, 0);
	c_wave_manage::get_instance()->refurbish_all_waves();
}

void startHostMonitor(void* phy_fb, int screen_width, int screen_height, int color_bytes)
{
	init();
	//Load UI.
	load_ui_single(phy_fb, screen_width, screen_height, color_bytes);
	//Start system.
	start_real_timer(wave_refresh_timer_callback);
    while(1)
    {
        thread_sleep(1000000);
    }
}
