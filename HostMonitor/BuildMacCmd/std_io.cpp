#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LOOP_SNAPSHOT_INTERVAL	50	//milli seconds.

extern void create_thread(unsigned long* thread_id, void* attr, void *(*start_routine) (void *), void* arg);
extern void thread_sleep(unsigned int milli_seconds);

extern int captureUiOfHostMonitor(int display);
extern void sendTouch2HostMonitor(int x, int y, bool is_down);

static int get_std_input(char *buffer, int size);
static const char* s_tip_help =
"-------------------- Help ------------------------\n"
"ss: 	Snapshot all screens in snapshot_N.bmp.\n"
"sslp: 	Snapshot in loop\n"
"aaN: 	Screen N flip left		N: 0-8\n"
"ddN: 	Screen N flip right		N: 0-8\n"
"exit: 	Exit the App.\n"
"--------------------------------------------------\n";

static bool s_is_loop_snapshot = false;

static void* loop_snapshot(void* param)
{
	int display_cnt = *(int*)(param);

	printf("Loop snapshot start...\n");
	printf("Snapshot per 50 millisecond\n>");
	fflush(stdout);
	while (s_is_loop_snapshot)
	{
		for (int i = 0; i < display_cnt; i++)
		{
			captureUiOfHostMonitor(i);
		}
		thread_sleep(LOOP_SNAPSHOT_INTERVAL);
	}
	printf("Loop snapshot exit\n>");
	fflush(stdout);
	return NULL;
}

static void press_down(int x, int y, int display_id)
{
	sendTouch2HostMonitor(x, y, true);
}

static void press_release(int x, int y, int display_id)
{
	sendTouch2HostMonitor(x, y, false);
}

static void left_flip(int display_id)
{
	press_down(0, 100, display_id);
	press_release(200, 100, display_id);
	printf("Screen %d left flip done.", display_id);
}

static void right_flip(int display_id)
{
	press_down(200, 100, display_id);
	press_release(0, 100, display_id);
	printf("Screen %d right flip done.", display_id);
}

static void* stdin_thread(void* param)
{
	int display_cnt = *(int*)(param);
	char buffer[64];

	while (true)
	{
		memset(buffer, 0, sizeof(buffer));
		printf("\n>");
		fflush(stdout);

		if (0 >= get_std_input(buffer, sizeof(buffer)))
		{
			continue;
		}

		if (strcmp(buffer, "exit") == 0)
		{
			exit(-1);
		}
		else if (strcmp(buffer, "ss") == 0)
		{
			for (int i = 0; i < display_cnt; i++)
			{
				captureUiOfHostMonitor(i);
			}
			printf("snapshot done.");
		}
		else if (strcmp(buffer, "sslp") == 0)
		{
			s_is_loop_snapshot = (s_is_loop_snapshot) ? false : true;
			if (s_is_loop_snapshot)
			{
				unsigned long pid;
				create_thread(&pid, NULL, loop_snapshot, param);
			}
		}
		else if (strstr(buffer, "aa") == buffer)
		{
			int display_id = atoi(&buffer[2]);
			if (display_id < 0 || display_id > 8)
			{
				printf("Bad screen ID, should be in 0~8");
				continue;
			}
			left_flip(display_id);
		}
		else if (strstr(buffer, "dd") == buffer)
		{
			int display_id = atoi(&buffer[2]);
			if (display_id < 0 || display_id > 8)
			{
				printf("Bad screen ID, should be in 0~8");
				continue;
			}
			right_flip(display_id);
		}
		else if (strstr(buffer, "press") == buffer)
		{
			int x, y;
			sscanf(buffer, "%*[a-z|(]%d,%d", &x, &y);
			press_down(x, y, 0);
			printf(buffer);
		}
		else if (strstr(buffer, "release") == buffer)
		{
			int x, y;
			sscanf(buffer, "%*[a-z|(]%d,%d", &x, &y);
			press_release(x, y, 0);
			printf(buffer);
		}
		else
		{
			printf("%s -- unknow command!", buffer);
			printf(s_tip_help);
		}
	}
}

void init_std_io(int display_cnt)
{
	unsigned long pid;
	static int s_display_cnt = display_cnt;
	create_thread(&pid, NULL, stdin_thread, &s_display_cnt);
#ifdef _WIN32
	s_is_loop_snapshot = true;
	create_thread(&pid, NULL, loop_snapshot , &s_display_cnt);
#endif
}

int get_std_input(char *buffer, int size)
{
	if (!fgets(buffer, (int)size - 1, stdin))
	{
		thread_sleep(10000);
		perror("fgets() failed!\n");
		fflush(stdout);
		return -1;
	}

	int len = (int)strlen(buffer) - 1;
	if (buffer[len] == '\n')
	{
		buffer[len] = '\0';
	}
	return len;
}
