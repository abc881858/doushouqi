#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

// one ChartView has one LeftWidget
// to show different checkbox open or close

#include <QFormLayout>
#include <QList>
#include <QWidget>

class LeftWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftWidget(QWidget *parent = nullptr);
    QList<int> list;

signals:
    void openCheck(int);
    void closeCheck(int);
};

#endif // LEFTWIDGET_H
