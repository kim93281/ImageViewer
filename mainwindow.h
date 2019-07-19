#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QDir>
#include <QtCore>
#include <QDebug>

#include <filedetection.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool m_change_check_ = false;
    void print_image(QString file_path);

private slots:
    void test_loof();
    void folder_detection();
    void new_file_slection();
    void on_prev_image_btn_clicked();
    void on_next_image_btn_clicked();
    void on_quit_btn_clicked();
    void on_fileListWidget_itemActivated(QListWidgetItem *item);

signals:
    void sig_send_mainwindow(QMainWindow *mainwindow);
};

#endif // MAINWINDOW_H
