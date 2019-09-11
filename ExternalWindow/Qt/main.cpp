#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    unsigned int share_id = 1;	//0 will be invalid.
    int width = 1024;
    int height = 768;

    if(argc == 2)
    {
    	share_id = atoi(argv[1]);
    }
    else if(argc == 4)
    {
		share_id = atoi(argv[1]);
		width = atoi(argv[2]);
		height = atoi(argv[3]);
    }

    if(0 > w.init(share_id, width, height))
    {
    	printf("create shared frame buffer failed! augments maybe invalid");
        return -2;
    }

    w.show();
    return a.exec();
}
