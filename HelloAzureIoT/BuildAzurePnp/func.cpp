#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>

extern "C" char* getDeviceInfo()
{
    static char info[128];
    static FILE *fp;

    if (fp != NULL)
    {
        return info;
    }

    fp = popen("uname -s -n -m ", "r");
    if (NULL == fp)
    {
        perror("popen failed");
        return NULL;
    }

    while (fgets(info, sizeof(info), fp) != NULL);
    info[strcspn(info, "\n")] = 0;//remove '\r' for json requirment
    info[strcspn(info, "\r")] = 0;//remove '\n' for json requirment

    pclose(fp);
    return info;
}

extern "C" char* getCurrentUtcTime()
{
    static char time_str[128];
    time_t currentTime = time(NULL);
    assert(strftime(time_str, sizeof(time_str), "%Y-%m-%dT%H:%M:%SZ", gmtime(&currentTime)));
    return time_str;
}
