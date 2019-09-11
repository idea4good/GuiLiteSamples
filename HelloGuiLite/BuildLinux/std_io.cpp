#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern void create_thread(unsigned long* thread_id, void* attr, void *(*start_routine) (void *), void* arg);
extern void thread_sleep(unsigned int milli_seconds);
extern void sendTouch2helloGL(int x, int y, bool is_down);
extern int captureUiOfhelloGL();

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

static void press_down(int x, int y)
{
	sendTouch2helloGL(x, y, true);
}

static void press_release(int x, int y)
{
	sendTouch2helloGL(x, y, false);
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
			captureUiOfhelloGL();
			printf("snapshot done.");
		}
		else if (strcmp(buffer, "bb") == 0)
		{
			press_down(10, 690);
			press_release(10, 690);
			printf("start button pressed.");
		}
		else if (strstr(buffer, "press") == buffer)
		{
			int x, y;
			sscanf(buffer, "%*[a-z|(]%d,%d", &x, &y);
			press_down(x, y);
			printf(buffer);
		}
		else if (strstr(buffer, "release") == buffer)
		{
			int x, y;
			sscanf(buffer, "%*[a-z|(]%d,%d", &x, &y);
			press_release(x, y);
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
