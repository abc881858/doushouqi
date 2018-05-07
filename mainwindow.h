#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QStackedWidget>
#include <QTime>
#include <QWidget>
#include <QtAV/AVPlayer.h>
#include <QtAV/Statistics.h>
#include <QtAVWidgets/VideoPreviewWidget.h>
#include "chartwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QStackedWidget *leftStack;
    QWidget *right;
    QWidget *left;
    QGridLayout *gridLayout;
    QVBoxLayout *vboxLayout;
    QLabel *pictureLabel;
    QImage m_image;
    QDialog *dialog;

private:
    QtAV::VideoPreviewWidget *m_preview;
    int m_duration;

};

#endif // MAINWINDOW_H
