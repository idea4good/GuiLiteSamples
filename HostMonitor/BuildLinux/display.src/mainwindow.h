#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void paintEvent(QPaintEvent* p);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    int init(unsigned int id, int width, int height);
private:
    void*           m_fb;
    int             m_width;
    int             m_height;
    unsigned int    m_share_id;
    char            m_hid_pipe_name[64];
    int             m_hid_fd;
    bool            m_is_pressed;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
