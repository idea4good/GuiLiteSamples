#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern void create_thread(unsigned long* thread_id, void* attr, void *(*start_routine) (void *), void* arg);
extern void thread_sleep(unsigned int milli_seconds);
extern int captureUiOfHelloScroll();
extern void sendTouch2HelloScroll(int x, int y, bool is_down);
extern void sendKey2HelloScroll(unsigned int key);

static int get_std_input(char *buffer, int size)
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

static void* stdin_thread(void* param)
{
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

		if (strstr(buffer, "press") == buffer)
		{
			int x, y;
			sscanf(buffer, "%*[a-z|(]%d,%d", &x, &y);
			printf(buffer);
			sendTouch2HelloScroll(x, y, true);
		}
		else if (strstr(buffer, "release") == buffer)
		{
			int x, y;
			sscanf(buffer, "%*[a-z|(]%d,%d", &x, &y);
			printf(buffer);
			sendTouch2HelloScroll(x, y, false);
		}
		else if (strcmp(buffer, "d") == 0)
		{
			sendKey2HelloScroll(0);
			printf("forward pressed.");
		}
		else if (strcmp(buffer, "a") == 0)
		{
			sendKey2HelloScroll(1);
			printf("backward pressed.");
		}
		else if (strcmp(buffer, "s") == 0)
		{
			sendKey2HelloScroll(2);
			printf("click pressed.");
		}
		else
		{
			printf("%s -- unknow command!", buffer);
		}
	}
}

void init_std_io()
{
	unsigned long pid;
	create_thread(&pid, NULL, stdin_thread, NULL);
}
