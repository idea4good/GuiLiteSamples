#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

extern int startHostMonitor(void** main_fbs, int main_cnt, int main_width, int main_height, void** sub_fbs, int sub_cnt, int sub_width, int sub_height, int color_bytes);
extern void init_std_io(int display_cnt);

static void* get_embeded_fb_in_display_app(int shared_id);
static void* get_dev_fb(char* path, int &width, int &height, int &color_bytes);

typedef int(*SYNC_DATA)(int hr, int spo2, int rr, int nibp_sys, int nibp_dia, int nibp_mean);
extern SYNC_DATA gSyncData;
static int sync_data(int hr, int spo2, int rr, int nibp_sys, int nibp_dia, int nibp_mean);

enum FRAMEBUFFER_MODE
{
	FB_NULL_MODE,
	FB_APP_MODE,
	FB_DEV_MODE
};
static const char* s_tip_welcome =
"-------------------------------------------------------------------\n"
"*  GuiLite Sample code [Version 1.6]                              *\n"
"*  Any feedback will be appreciated. Email: idea4good@outlook.com *\n"
"-------------------------------------------------------------------\n"
"How to run with Internet browser?\n"
"1. Run Display.html with your internet browser:\n"
"2. Type command: sslp\n\n"

"How to run inside QT APP?\n"
"If x64: ./display-x64 | ./HostMonitor shared-fb\n"
"If ARM: ./display-arm | ./HostMonitor shared-fb\n\n"

"How to run on Linux?\n"
"Type command: ./HostMonitor /dev/fb-path\n\n";

int main(int argc, char** argv)
{
	printf(s_tip_welcome);

	int main_cnt = 1;
	int sub_cnt = 0;
	int color_bytes = 2;
	int main_screen_width = 1024;
	int main_screen_height = 768;
	int sub_screen_width = 1024;
	int sub_screen_height = 370;

	system("open Display.html");
    gSyncData = sync_data;
    sync_data(60, 98, 30, 120, 80, 100);//ping cloud

	FRAMEBUFFER_MODE fb_mode = FB_NULL_MODE;
	char *fb_dev_path = NULL;

	int share_id = 1;//should be same with display app.

	if (argc == 3)
	{
		main_cnt = atoi(argv[1]);
		sub_cnt = atoi(argv[2]);

		if (main_cnt < 0 || main_cnt > 1)
		{
			printf("Invalid argument: main_cnt(0~1)\n");
			return -1;
		}
		if (sub_cnt < 0 || sub_cnt > 8)
		{
			printf("Invalid argument: sub_cnt(0~8)\n");
			return -1;
		}
	}
	else if(argc == 2)
	{
		char* argument = argv[1];
		if(strcmp(argument,"shared-fb") == 0)
		{
			fb_mode = FB_APP_MODE;
			
		}
		else if(strncmp(argument, "/dev/", 5) == 0)
		{
			fb_dev_path = argument;
			fb_mode = FB_DEV_MODE;
		}
		else
		{
			printf("Invalid argument, should be: shared-fb, or framebuffer path\n");
			return -1;
		}
		
	}

	void** main_fbs = (void**)malloc(sizeof(void*) * main_cnt);
	void** sub_fbs = (void**)malloc(sizeof(void*) * sub_cnt);
	for (int i = 0; i < main_cnt; i++)
	{
		switch(fb_mode)
		{
			case FB_APP_MODE:
				main_fbs[i] = get_embeded_fb_in_display_app(share_id);
			break;
			case FB_DEV_MODE:
				//main_fbs[i] = get_dev_fb(fb_dev_path, main_screen_width, main_screen_height, color_bytes);
			break;
			default:
				main_fbs[i] = calloc(main_screen_width * main_screen_height, color_bytes);
			break;
		}
	}
	for (int i = 0; i < sub_cnt; i++)
	{
		sub_fbs[i] = calloc(sub_screen_width * sub_screen_height, color_bytes);
	}

	init_std_io((main_cnt + sub_cnt));
	return startHostMonitor(main_fbs, main_cnt, main_screen_width, main_screen_height, sub_fbs, sub_cnt, sub_screen_width, sub_screen_height, color_bytes);	//never return;
}

static void* get_embeded_fb_in_display_app(int shared_id)
{
	void* ret = NULL;
	while(ret == NULL)
	{
		int shmid = shmget(shared_id, 0, SHM_R | SHM_W);
		if (shmid >= 0)
		{
			if(ret = (unsigned char*)shmat(shmid, 0, 0))
			{
				break;
			}
			printf("shmat failed! run display app first.\n");
		}
		else
		{
			printf("shmget failed! run display app first\n");
		}
		sleep(1);
	}
	return ret;
}

int sync_data(int hr, int spo2, int rr, int nibp_sys, int nibp_dia, int nibp_mean)
{
    char cmd_line[128];
    memset(cmd_line, 0, sizeof(cmd_line));
    sprintf(cmd_line, "%s %d %d %d %d %d %d",
            "./.sync_data.sh ",
            hr, spo2, rr, nibp_sys, nibp_dia, nibp_mean);
    return system(cmd_line);
}
