#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdio.h>

int WINDOW_WIDTH = 256;
int WINDOW_HEIGHT = 256;
void* GuiLiteFb;
pthread_mutex_t mutex;

void updateImgFromGuiLite(XImage *img)
{
    if(!GuiLiteFb)
    {
        return;
    }

    unsigned short* pixel = (unsigned short*)GuiLiteFb;
	for (int y = 0; y < WINDOW_HEIGHT; ++y)
    {
       for (int x = 0; x < WINDOW_WIDTH; ++x)
        {
            unsigned int rgb = *pixel++;
            rgb = ((0xFF << 24) | ((((unsigned int)(rgb)) & 0x1F) << 3) | ((((unsigned int)(rgb)) & 0x7E0) << 5) | ((((unsigned int)(rgb)) & 0xF800) << 8));
            XPutPixel(img, x, y, rgb);
        } 
    }
}

void parseArgument(int argc, char **argv)
{
    if(argc != 3)
    {
        return;
    }

    unsigned int share_id = 1;
    WINDOW_WIDTH = atoi(argv[1]);
    WINDOW_HEIGHT = atoi(argv[2]);

    int fb_size = (WINDOW_WIDTH * WINDOW_HEIGHT * 2);
    int shmid = shmget(share_id, fb_size, SHM_R | SHM_W | IPC_CREAT );
    if(-1 == shmid)
    {
        if(22 == errno)
        {
            printf("ipcrm -M 1\nand restart.\n");
        }
        printf("shmget failed");
    }

    GuiLiteFb = shmat(shmid, 0, 0);
    if((void*)-1 != GuiLiteFb)
    {
        memset(GuiLiteFb, 0, fb_size);
    }
    else
    {
        printf("shmat failed");
    }
    fflush(stdout);
}

void* inputThread(void* display)
{
    int x11_fd = ConnectionNumber(display);
    fd_set in_fds;
    XEvent event;
    struct timeval tv;

    while(1)
    {
        FD_ZERO(&in_fds);
        FD_SET(x11_fd, &in_fds);
        tv.tv_usec = 0;
        tv.tv_sec = 1;

        int num_ready_fds = select(x11_fd + 1, &in_fds, NULL, NULL, &tv);
        if (num_ready_fds > 0)
        {//received event
            pthread_mutex_lock(&mutex);
            while(XPending(display))
            {
                XNextEvent(display, &event);//non blocking
                switch(event.type)
                {
                    case ButtonPress:
                        printf("press(%d,%d)\n", event.xbutton.x, event.xbutton.y);
                    break;
                    case ButtonRelease:
                        printf("release(%d,%d)\n", event.xbutton.x, event.xbutton.y);
                    break;
                }
                fflush(stdout);
            }
            pthread_mutex_unlock(&mutex);
        }
    }
}

int main(int argc,char **argv)
{
	parseArgument(argc, argv);
    pthread_mutex_init(&mutex, 0);

	//init display
	Display* display = XOpenDisplay(NULL);
	int screen_num = DefaultScreen(display);
	Window root = RootWindow(display, screen_num);
	Visual *visual = DefaultVisual(display, screen_num);
	int colorBits = DefaultDepth(display, screen_num);
	char *data = (char*)malloc(WINDOW_WIDTH * WINDOW_HEIGHT * colorBits);
	
	//Create/Show window
	Window win = XCreateSimpleWindow(display, root, 50, 50, WINDOW_WIDTH, WINDOW_HEIGHT, 1, 0, 0);
	XSelectInput(display, win, ExposureMask | ButtonPressMask| ButtonReleaseMask);
	XMapWindow(display, win);

    //Start input thread
    pthread_t pid;
    pthread_create(&pid, NULL, inputThread, display);

    //create img for GuiLite framebuffer
    XImage *img = XCreateImage(display, visual, colorBits, ZPixmap, 0, data, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0);

	//Main loop
    GC gc = DefaultGC(display,screen_num);
	while(1)
	{
		updateImgFromGuiLite(img);
        pthread_mutex_lock(&mutex);
		XPutImage(display, win, gc, img, 0, 0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        pthread_mutex_unlock(&mutex);
		usleep(30000);
	}
	XCloseDisplay(display);
	return 0;
}
