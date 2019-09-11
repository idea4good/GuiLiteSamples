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

int startHostMonitor(void** main_fbs, int main_cnt, int main_width, int main_height, void** sub_fbs, int sub_cnt, int sub_width, int sub_height, int color_bytes);
int sendTouch2HostMonitor(void* buf, int len,int dispId);
void* getUiOfHostMonitor(int dispId,int* width, int* height, bool force_update);
void *mainBuff[4]={0};
void *subBuff[4]={0};

#define UI_WIDTH 1024
#define UI_HEIGHT 768
#define SUB_WIDTH 1024
#define SUB_HEIGHT 370
class GuiLiteThread: public QThread
{

    void run()
    {
        mainBuff[0]=calloc(UI_WIDTH * UI_HEIGHT, 2);
        subBuff[0]=calloc(SUB_WIDTH * SUB_HEIGHT, 2);

        startHostMonitor(mainBuff,1, UI_WIDTH, UI_HEIGHT,subBuff,1, SUB_WIDTH, SUB_HEIGHT, 2);
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_is_pressed = false;
    ui->setupUi(this);
  //  this->setMouseTracking(true);
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
    void* fb = getUiOfHostMonitor(0,NULL, NULL, fore_update);
    if(fb){
        QPainter painter(this);
        QImage img((uchar*)fb, UI_WIDTH, UI_HEIGHT, QImage::Format_RGB16);
        painter.drawImage(0, 0, img);
        fore_update = false;
    }
    fb = getUiOfHostMonitor(1,NULL, NULL, fore_update);
    if(fb){
        QPainter painter(this);
        QImage img((uchar*)fb, SUB_WIDTH, SUB_HEIGHT, QImage::Format_RGB16);
        painter.drawImage(0, 768, img);
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
    sendTouch2HostMonitor(&msg,sizeof(msg),0);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    m_is_pressed = false;
    MSG_INFO msg;
    msg.dwMsgId = 0x4600;
    msg.dwParam1 = e->x();
    msg.dwParam2 = e->y();

    sendTouch2HostMonitor(&msg,sizeof(msg),0);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(m_is_pressed)
    {
        mousePressEvent(e);
    }
}
