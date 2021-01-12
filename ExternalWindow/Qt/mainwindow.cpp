#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <qtimer.h>
#include <QMouseEvent>
#include <sys/shm.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_share_id = 1; //0 will be invalid.
    m_fb = NULL;
    m_width = 1024;
    m_height = 768;
    m_hid_fd = -1;
    memset(m_hid_pipe_name, 0, sizeof(m_hid_pipe_name));
    m_is_pressed = false;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(30);//30ms

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::init(unsigned int id, int width, int height)
{
    m_share_id = id;
    m_width = width;
    m_height = height;

    setFixedHeight(m_height);
    setFixedWidth(m_width);

    int fb_size = (width * height * 2);

    int shmid = shmget(m_share_id, fb_size, SHM_R | SHM_W | IPC_CREAT );
    
    if((-1 == shmid) && (22 == errno))
    {
        system("ipcrm -M 1");
        shmid = shmget(m_share_id, fb_size, SHM_R | SHM_W | IPC_CREAT );
    }
    if(-1 == shmid)
    {
        printf("shmget failed shmid: %d, error = %d", shmid, errno);
    }
    
    m_fb = shmat(shmid, 0, 0);
    if((void*)-1 != m_fb)
    {
        memset(m_fb, 0, fb_size);
    }
    else
    {
        return -2;
    }

    sprintf(m_hid_pipe_name, "./hid_pipe_%d", id);
    return 0;
}

void MainWindow::paintEvent(QPaintEvent* p)
{
    p = p;//kill warning.
    QPainter painter(this);

    if((void*)(-1) != m_fb)
    {
        QImage img((uchar*)m_fb, m_width, m_height, QImage::Format_RGB16);
        painter.drawImage(0, 0, img);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    m_is_pressed = true;
    printf("press(%d,%d)\n", e->pos().x(), e->pos().y());
    fflush(stdout);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    m_is_pressed = false;
    printf("release(%d,%d)\n", e->pos().x(), e->pos().y());
    fflush(stdout);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(m_is_pressed)
    {
        mousePressEvent(e);
    }
}
