#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCREEN_WIDTH	1024
#define SCREEN_HEIGHT	768

extern "C" int run_native(int width, int height, void* phy_fb);
extern void init_std_io(int display_cnt);

static void init_dump();
static void* make_fb_shared_by_display_app(int shared_id);
static const char* s_tip_welcome =
"-------------------------------------------------------------------\n"
"*  GuiLite Sample code [Version 1.6]                              *\n"
"*  Any feedback will be appreciated. Email: idea4good@outlook.com *\n"
"-------------------------------------------------------------------\n"
"How to run on PC/Desktop?\n"
"1. Run Display.html with your internet browser:\n"
"2. Type command: sslp\n\n";

int main(int argc, char** argv)
{
	printf(s_tip_welcome);
	init_dump();

	bool is_shared_fb = false;
	int share_id = 1;//should be same with display app.

	if(argc == 2)
	{
		char* argument = argv[1];
		if(strcmp(argument,"shared-fb") != 0)
		{
			printf("Invalid argument, should be: shared-fb\n");
			return -1;
		}
		is_shared_fb = true;
	}

	init_std_io(1);

	void* phy_fb = 0;
	if(is_shared_fb)
	{
		phy_fb = make_fb_shared_by_display_app(share_id);
	}
	else
	{
		phy_fb = calloc(SCREEN_WIDTH * SCREEN_HEIGHT * 2, 1);
	}
	return run_native(SCREEN_WIDTH, SCREEN_HEIGHT, phy_fb);//never return;
}

#ifdef __linux__
#include <sys/shm.h>
#include <unistd.h>
#include <signal.h>
#include <execinfo.h>
#include <assert.h>
#include <errno.h>

#define DUMP_BUF_SIZE 1024
#define DUMP_FILE_PATH "dump.txt"

static void *s_dump_buffer[DUMP_BUF_SIZE];
static const char *s_seg_start = ".....segment fault.....\n";
static const char *s_assert_start = ".....assert.....\n";
static const char *s_end = ".....end.....\n";

void do_assert(const char* file, int line)
{
	printf("assert! file:%s,line:%d,error no: %d\n", file, line, errno);

	int num;
	char **calls;
	num = backtrace(s_dump_buffer, DUMP_BUF_SIZE);
	calls = backtrace_symbols(s_dump_buffer, num);
	for (int i = 0; i < num; i++)
	{
		printf("%s\n", calls[i]);
	}

	char string[256];
	memset(string, 0, sizeof(string));

	FILE *fp = fopen(DUMP_FILE_PATH, "ab+");
	fwrite(s_assert_start, sizeof(unsigned char), strlen(s_assert_start), fp);

	sprintf(string, "file:%s,line:%d,error no: %d\n", file, line, errno);
	fwrite(string, sizeof(unsigned char), strlen(string), fp);

	for (int i = 0; i < num; i++)
	{
		fwrite(calls[i], sizeof(unsigned char), strlen(calls[i]), fp);
		fwrite("\n", sizeof(unsigned char), 1, fp);
	}
	fwrite(s_end, sizeof(unsigned char), strlen(s_end), fp);
	assert(0);
	_exit(-1);
}

void log_out(const char* log)
{
	printf(log);
	fflush(stdout);
}

static void write_dump_file(char **calls, int num)
{
	FILE *fp;
	fp = fopen(DUMP_FILE_PATH, "ab+");

	fwrite(s_seg_start, sizeof(unsigned char), strlen(s_seg_start), fp);
	if (fp != NULL)
	{
		for (int i = 0; i < num; i++)
		{
			fwrite(calls[i], sizeof(unsigned char), strlen(calls[i]), fp);
			fwrite("\n", sizeof(unsigned char), 1, fp);
		}
		fwrite(s_end, sizeof(unsigned char), strlen(s_end), fp);
		fclose(fp);
	}
}

static void dump_segment_fault(int n, siginfo_t *siginfo, void *myact)
{
	printf("segment fault! addr:0x%X\n", siginfo->si_addr);

	int num;
	char **calls;
	num = backtrace(s_dump_buffer, DUMP_BUF_SIZE);
	calls = backtrace_symbols(s_dump_buffer, num);
	for (int i = 0; i < num; i++)
	{
		printf("%s\n", calls[i]);
	}
	write_dump_file(calls, num);
	_exit(-1);
}

static void init_dump()
{
	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = dump_segment_fault;
	sigaction(SIGSEGV, &act, NULL);
	signal(SIGCLD, SIG_IGN);
}

static void* make_fb_shared_by_display_app(int shared_id)
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
	sleep(1);//wait display app init.
	return ret;
}
#else

#include <windows.h>
#include <assert.h>

void do_assert(const char* file, int line)
{
	printf("assert! file:%s,line:%d\n", file, line);
	assert(false);
}

void log_out(const char* log)
{
	printf(log);
	fflush(stdout);
	OutputDebugStringA(log);
}

static void* make_fb_shared_by_display_app(int shared_id)
{
	printf("shared frame buffer support Linux only!\n");
	exit(-4);
	return NULL;
}

static void init_dump()
{
}
#endif
