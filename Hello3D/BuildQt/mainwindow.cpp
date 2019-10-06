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

extern "C" void startHello3D(void* phy_fb, int width, int height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op);
extern void* getUiOfHello3D(int* width, int* height, bool force_update);

#define UI_WIDTH 480
#define UI_HEIGHT 320
class GuiLiteThread: public QThread
{
    void run()
    {
        startHello3D(calloc(UI_WIDTH * UI_HEIGHT, 2), UI_WIDTH, UI_HEIGHT, 2, NULL);
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
    setFixedWidth(600);
    setFixedHeight(400);

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
    void* fb = getUiOfHello3D(NULL, NULL, fore_update);
    if(fb){
        QPainter painter(this);
        QImage img((uchar*)fb, UI_WIDTH, UI_HEIGHT, QImage::Format_RGB16);
        painter.drawImage(0, 0, img);
        fore_update = false;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{}
