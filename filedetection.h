#ifndef FILEDETECTION_H
#define FILEDETECTION_H

#include <mainwindow.h>
#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include <QDir>
#include <QListWidget>

class FileDetection : public QThread
{
public:
    FileDetection(QListWidget *fileListWidget);
protected:
    void run();
private:
    QListWidget *fileListWidget = nullptr;
};

#endif // FILEDETECTION_H
