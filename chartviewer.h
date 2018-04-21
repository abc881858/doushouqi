#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include "qchartviewer.h"
#include <QScrollBar>

class ChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChartWidget(QWidget *parent = nullptr,int r =0, int c=0);
    QChartViewer *m_viewer;
    XYChart *m_chart;

    DoubleArray m_timeStamps;
    DoubleArray m_dataSeriesA;
    DoubleArray m_dataSeriesB;
    DoubleArray m_dataSeriesC;

    QViewPortControl *m_ViewPortControl;
    void trackLineLegend(XYChart *c, int mouseX);

    int w;
    int h;

signals:

public slots:
    void onViewPortChanged();
    void onMouseMovePlotArea(QMouseEvent *);
};

#endif // CHARTWIDGET_H
