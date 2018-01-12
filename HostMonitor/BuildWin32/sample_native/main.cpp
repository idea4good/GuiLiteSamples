#include <windows.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <shellapi.h>

extern int startHostMonitor(void** main_fbs, int main_cnt, int main_width, int main_height, void** sub_fbs, int sub_cnt, int sub_width, int sub_height, int color_bytes);
extern void init_std_io(int display_cnt);
static const char* s_tip_welcome =
"-------------------------------------------------------------------\n"
"*  GuiLite Sample code [Version 1.6]                              *\n"
"*  Any feedback will be appreciated. Email: idea4good@outlook.com *\n"
"-------------------------------------------------------------------\n";

static void launchIE()
{
	int ret = (int)ShellExecute(0, L"open", L"Display.html", L"", L"", SW_SHOWNORMAL);
	if (SE_ERR_NOASSOC >= ret)
	{
		switch (ret)
		{
		case SE_ERR_FNF:
			printf("Error: Display.html not found!");
			break;
		case SE_ERR_ACCESSDENIED:
			printf("Error: Display.html access denied!");
			break;
		default:
			printf("Error: Execute Display.html failed!");
			break;
		}
	}
}

int main(int argc, char** argv)
{
	int main_cnt = 1;
	int sub_cnt = 0;
	int color_bytes = 2;
	int main_screen_width = 1024;
	int main_screen_height = 768;
	int sub_screen_width = 1024;
	int sub_screen_height = 370;

	printf(s_tip_welcome);
	launchIE();

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

	init_std_io((main_cnt + sub_cnt));

	void** main_fbs = (void**)malloc(sizeof(void*) * main_cnt);
	void** sub_fbs = (void**)malloc(sizeof(void*) * sub_cnt);
	for (int i = 0; i < main_cnt; i++)
	{
		main_fbs[i] = calloc(main_screen_width * main_screen_height, color_bytes);
	}
	for (int i = 0; i < sub_cnt; i++)
	{
		sub_fbs[i] = calloc(sub_screen_width * sub_screen_height, color_bytes);
	}
	return startHostMonitor(main_fbs, main_cnt, main_screen_width, main_screen_height, sub_fbs, sub_cnt, sub_screen_width, sub_screen_height, color_bytes);	//never return;
}

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

