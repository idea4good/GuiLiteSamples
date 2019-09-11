#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <qtimer.h>
#include <QMouseEvent>
#include <QThread>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "msg.h"

void start_helloGL(void* phy_fb, int width, int height, int color_bytes);
int sendTouch2helloGL(void* buf, int len);
void* getUiOfhelloGL(int* width, int* height, bool force_update);

#define UI_WIDTH 680
#define UI_HEIGHT 512
class GuiLiteThread: public QThread
{
    void run()
    {
        start_helloGL(calloc(UI_WIDTH * UI_HEIGHT, 2), UI_WIDTH, UI_HEIGHT, 2);
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_is_pressed = false;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    setAttribute(Qt::WA_NoBackground);
    setFixedHeight(UI_HEIGHT);
    setFixedWidth(UI_WIDTH);

    GuiLiteThread* thread = new GuiLiteThread;
    thread->start();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(30);//30ms
}

void MainWindow::paintEvent(QPaintEvent* p)
{
    (void)p;//kill warning.
    static bool fore_update = true;
    void* fb = getUiOfhelloGL(NULL, NULL, fore_update);
    if(fb){
        QPainter painter(this);
        QImage img((uchar*)fb, UI_WIDTH, UI_HEIGHT, QImage::Format_RGB16);
        painter.drawImage(0, 0, img);
        fore_update = false;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    m_is_pressed = true;
    MSG_INFO msg;
    msg.dwMsgId = 0x4700;
    msg.dwParam1 = e->x();
    msg.dwParam2 = e->y();
    sendTouch2helloGL(&msg,sizeof(msg));
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    m_is_pressed = false;
    MSG_INFO msg;
    msg.dwMsgId = 0x4600;
    msg.dwParam1 = e->x();
    msg.dwParam2 = e->y();

    sendTouch2helloGL(&msg,sizeof(msg));
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(m_is_pressed)
    {
        mousePressEvent(e);
    }
}
