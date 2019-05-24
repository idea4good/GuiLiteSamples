#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern void create_thread(unsigned long* thread_id, void* attr, void *(*start_routine) (void *), void* arg);
extern void thread_sleep(unsigned int milli_seconds);
extern int captureUiOfHelloNoTouch();
extern "C" void sendTouch2HelloNoTouch(int x, int y, bool is_down);
extern "C" void sendKey2HelloNoTouch(unsigned int key);

static int get_std_input(char *buffer, int size)
{
	if (!fgets(buffer, (int)size - 1, stdin))
	{
		thread_sleep(10000);
		printf("Warning: fgets() failed!\n");
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

		if (strcmp(buffer, "exit") == 0)
		{
			exit(-1);
		}
		else if (strcmp(buffer, "ss") == 0)
		{
			captureUiOfHelloNoTouch();
			printf("snapshot done.");
		}
		else if (strcmp(buffer, "d") == 0)
		{
			sendKey2HelloNoTouch(0);
			printf("forward pressed.");
		}
		else if (strcmp(buffer, "a") == 0)
		{
			sendKey2HelloNoTouch(1);
			printf("backward pressed.");
		}
		else if (strcmp(buffer, "s") == 0)
		{
			sendKey2HelloNoTouch(2);
			printf("click pressed.");
		}
		else if (strstr(buffer, "press") == buffer)
		{
			int x, y;
			sscanf(buffer, "%*[a-z|(]%d,%d", &x, &y);
			sendTouch2HelloNoTouch(x, y, true);
			printf(buffer);
		}
		else if (strstr(buffer, "release") == buffer)
		{
			int x, y;
			sscanf(buffer, "%*[a-z|(]%d,%d", &x, &y);
			sendTouch2HelloNoTouch(x, y, false);
			printf(buffer);
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
