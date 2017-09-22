#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int run(void** main_fbs, int main_cnt, void** sub_fbs, int sub_cnt);
extern void init_std_io(int display_cnt);

static void init_dump();
static void* make_fb_shared_by_display_app(int shared_id);
static const char* s_tip_welcome =
"-------------------------------------------------------------------\n"
"*  Noodle UI Sample code [Version 1.6]                            *\n"
"*  Any feedback will be appreciated. Email: idea4good@outlook.com *\n"
"-------------------------------------------------------------------\n"
"How to run on PC/Desktop?\n"
"1. Run Display.html with your internet browser:\n"
"2. Type command: sslp\n\n"

"How to run on embedded Linux device?\n"
"Type command: sample_native/bin/sample_native path W H M N\n"
"  path: file path of frame buffer, for example: /dev/fb\n"
"  W:    Width of frame buffer, for example: 1024\n"
"  H:    Height of frame buffer, for example: 768\n"
"  M:    0\n"
"  N:    0~8\n\n";

int main(int argc, char** argv)
{
	printf(s_tip_welcome);

	remove("snapshot_0.bmp");
	remove("snapshot_1.bmp");
	remove("snapshot_2.bmp");
	remove("snapshot_3.bmp");
	remove("snapshot_4.bmp");
	remove("snapshot_5.bmp");
	remove("snapshot_6.bmp");
	remove("snapshot_7.bmp");
	remove("snapshot_8.bmp");

	init_dump();

	int main_cnt = 1;
	int sub_cnt = 0;
	bool is_shared_fb = false;
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
		if(strcmp(argument,"shared-fb") != 0)
		{
			printf("Invalid argument, should be: shared-fb\n");
			return -1;
		}
		is_shared_fb = true;
	}

	init_std_io((main_cnt + sub_cnt));

	void** main_fbs = (void**)malloc(sizeof(void*) * main_cnt);
	void** sub_fbs = (void**)malloc(sizeof(void*) * sub_cnt);
	for (int i = 0; i < main_cnt; i++)
	{
		if(is_shared_fb)
		{
			main_fbs[i] = make_fb_shared_by_display_app(share_id);
		}
		else
		{
			main_fbs[i] = calloc(1024 * 768 * 2, 1);
		}	
	}
	for (int i = 0; i < sub_cnt; i++)
	{
		sub_fbs[i] = calloc(1024 * 370 * 2, 1);
	}
	return run(main_fbs, main_cnt, sub_fbs, sub_cnt);	//never return;
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
