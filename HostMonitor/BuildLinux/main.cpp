#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <errno.h>
#include <sys/stat.h>

void startHostMonitor(void* phy_fb, int screen_width, int screen_height, int color_bytes);
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
"--------------------------- Help ---------------------------\n"
"Run on Linux Desktop:\n"
"./xWindow 1024 768 | ./HostMonitor shared-fb\n\n"

"Run on ARM Linux:\n"
"./HostMonitor /dev/fb-path\n\n"

"ss: 	Save UI in snapshot.bmp.\n"
"aa: 	Left slide.\n"
"dd:    Right slide.\n"
"------------------------------------------------------------\n";

int main(int argc, char** argv)
{
	printf(s_tip_welcome);
	
	int color_bytes = 2;
	int main_screen_width = 1024;
	int main_screen_height = 768;
    gSyncData = sync_data;

	//ping cloud
	system("chmod 777 .sync_build.sh");
	system("./.sync_build.sh HostMonitor > /dev/null 2>&1 &");
    system("chmod 777 .sync_data.sh");
    sync_data(60, 98, 30, 120, 80, 100);

	FRAMEBUFFER_MODE fb_mode = FB_NULL_MODE;
	char *fb_dev_path = NULL;

	int share_id = 1;//should be same with display app.
	if(argc == 2)
	{
		char* argument = argv[1];
		if(strcmp(argument,"shared-fb") == 0)
		{
			fb_mode = FB_APP_MODE;
			
		}
		else if(strncmp(argument, "/dev", 4) == 0)
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

	void* phy_fb;
	switch(fb_mode)
	{
		case FB_APP_MODE:
			phy_fb = get_embeded_fb_in_display_app(share_id);
		break;
		case FB_DEV_MODE:
			phy_fb = get_dev_fb(fb_dev_path, main_screen_width, main_screen_height, color_bytes);
		break;
		default:
			phy_fb = calloc(main_screen_width * main_screen_height, color_bytes);
		break;
	}
	init_std_io(1);
	startHostMonitor(phy_fb, main_screen_width, main_screen_height, color_bytes);//never return;
	return 0;
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
			perror("shmat failed! run display app first.\n");
		}
		else
		{
			perror("shmget failed! run display app first\n");
		}
		sleep(1);
	}
	return ret;
}

static void* get_dev_fb(char* path, int &width, int &height, int &color_bytes)
{
	int fd = open (path, O_RDWR);
	if(0 > fd)
	{
		perror("open fb failed!\n");
		_exit(-1);
	}

	struct fb_var_screeninfo vinfo;
	if (0 > ioctl(fd, FBIOGET_VSCREENINFO, &vinfo))
	{
		perror("get fb info failed!\n");
		_exit(-1);
    }

    width = vinfo.xres;
    height = vinfo.yres;
    color_bytes = vinfo.bits_per_pixel / 8;
    if (width & 0x3)
    {
        width = (width + 0x3) & (~0x3);
        printf("Warning: Round screen width to be multiple of 4.\n");
    }
    printf("vinfo.xres=%d\n",vinfo.xres);
    printf("vinfo.yres=%d\n",vinfo.yres);
    printf("vinfo.bits_per_pixel=%d\n",vinfo.bits_per_pixel);

	void* fbp = mmap(0, (vinfo.xres * vinfo.yres * color_bytes), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(fbp == MAP_FAILED)
	{
		perror("mmap fb failed!\n");  
		_exit(-1);
	}
	memset(fbp, 0, (vinfo.xres * vinfo.yres * color_bytes));
	return fbp;
}

int sync_data(int hr, int spo2, int rr, int nibp_sys, int nibp_dia, int nibp_mean)
{
    char cmd_line[128];
    memset(cmd_line, 0, sizeof(cmd_line));
    sprintf(cmd_line, "%s %d %d %d %d %d %d &",
            "./.sync_data.sh ",
            hr, spo2, rr, nibp_sys, nibp_dia, nibp_mean);
    return system(cmd_line);
}
