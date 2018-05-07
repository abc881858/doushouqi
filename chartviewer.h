#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H
 
// this file is for setting the Chart View
 
#include <QScrollBar>
#include <QWidget>
#include "qchartviewer.h"
 
class ChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChartWidget(QWidget *parent = nullptr, int r =0, int c=0, QList<int> list ={});
    QChartViewer *m_viewer;
    XYChart *down_chart;
    XYChart *up_chart;
 
    DoubleArray m_timeStamps;
 
    DoubleArray m_dataSeries_vehicle_vxy;
    DoubleArray m_dataSeries_vehicle_ax;
    DoubleArray m_dataSeries_vehicle_yawrate;
    DoubleArray m_dataSeries_record_vxy;
    DoubleArray m_dataSeries_record_ax;
    DoubleArray m_dataSeries_record_yawrate;
    DoubleArray m_dataSeries_front_wheel_angle;
    DoubleArray m_dataSeries_record_wheel_angle;
 
    DoubleArray m_back_collision_ibeoX;
    DoubleArray m_front_collision_ibeoX;
    DoubleArray m_back_collision_fusionX;
    DoubleArray m_front_collision_fusionX;
    DoubleArray m_cutin_collision_riskX;
    DoubleArray m_rear_end_collision_riskX;
    DoubleArray m_gapX;
    DoubleArray m_start_timestampX;
    DoubleArray m_footfault_hdmapX;
    DoubleArray m_footfault_dectectX;
    DoubleArray m_acc_differenceX;
    DoubleArray m_angle_differenceX;
    DoubleArray m_take_over_requestX;
    DoubleArray m_quit_take_overX;
 
    DoubleArray m_back_collision_ibeoY;
    DoubleArray m_front_collision_ibeoY;
    DoubleArray m_back_collision_fusionY;
    DoubleArray m_front_collision_fusionY;
    DoubleArray m_cutin_collision_riskY;
    DoubleArray m_rear_end_collision_riskY;
    DoubleArray m_gapY;
    DoubleArray m_start_timestampY;
    DoubleArray m_footfault_hdmapY;
    DoubleArray m_footfault_dectectY;
    DoubleArray m_acc_differenceY;
    DoubleArray m_angle_differenceY;
    DoubleArray m_take_over_requestY;
    DoubleArray m_quit_take_overY;
 
    DoubleArray viewPortDataSeries_vehicle_vxy;
    DoubleArray viewPortDataSeries_vehicle_ax;
    DoubleArray viewPortDataSeries_vehicle_yawrate;
    DoubleArray viewPortDataSeries_record_vxy;
    DoubleArray viewPortDataSeries_record_ax;
    DoubleArray viewPortDataSeries_record_yawrate;
    DoubleArray viewPortDataSeries_front_wheel_angle;
    DoubleArray viewPortDataSeries_record_wheel_angle;
 
    DoubleArray v_back_collision_ibeoX;
    DoubleArray v_front_collision_ibeoX;
    DoubleArray v_back_collision_fusionX;
    DoubleArray v_front_collision_fusionX;
    DoubleArray v_cutin_collision_riskX;
    DoubleArray v_rear_end_collision_riskX;
    DoubleArray v_gapX;
    DoubleArray v_start_timestampX;
    DoubleArray v_footfault_hdmapX;
    DoubleArray v_footfault_dectectX;
    DoubleArray v_acc_differenceX;
    DoubleArray v_angle_differenceX;
    DoubleArray v_take_over_requestX;
    DoubleArray v_quit_take_overX;
 
    DoubleArray v_back_collision_ibeoY;
    DoubleArray v_front_collision_ibeoY;
    DoubleArray v_back_collision_fusionY;
    DoubleArray v_front_collision_fusionY;
    DoubleArray v_cutin_collision_riskY;
    DoubleArray v_rear_end_collision_riskY;
    DoubleArray v_gapY;
    DoubleArray v_start_timestampY;
    DoubleArray v_footfault_hdmapY;
    DoubleArray v_footfault_dectectY;
    DoubleArray v_acc_differenceY;
    DoubleArray v_angle_differenceY;
    DoubleArray v_take_over_requestY;
    DoubleArray v_quit_take_overY;
 
    QViewPortControl *m_ViewPortControl;
    void trackLineLegend(XYChart *c, int mouseX);
 
    int w;
    int h;
    QList<int> l;
    double delt;
 
    LineLayer *upLayer;
    LineLayer *downLayer;
 
    ScatterLayer *upLayer8;
    ScatterLayer *upLayer9;
    ScatterLayer *upLayer10;
    ScatterLayer *upLayer11;
    ScatterLayer *upLayer12;
    ScatterLayer *upLayer13;
    ScatterLayer *upLayer14;
    ScatterLayer *upLayer15;
    ScatterLayer *upLayer16;
    ScatterLayer *upLayer17;
    ScatterLayer *upLayer18;
    ScatterLayer *upLayer19;
    ScatterLayer *upLayer20;
    ScatterLayer *upLayer21;
 
    ScatterLayer *downLayer8;
    ScatterLayer *downLayer9;
    ScatterLayer *downLayer10;
    ScatterLayer *downLayer11;
    ScatterLayer *downLayer12;
    ScatterLayer *downLayer13;
    ScatterLayer *downLayer14;
    ScatterLayer *downLayer15;
    ScatterLayer *downLayer16;
    ScatterLayer *downLayer17;
    ScatterLayer *downLayer18;
    ScatterLayer *downLayer19;
    ScatterLayer *downLayer20;
    ScatterLayer *downLayer21;
 
signals:
    void mouseClick(double delt);
    void changeLeftWidget();
 
public slots:
    void onViewPortChanged();
    void onMouseMovePlotArea(QMouseEvent *);
};
 
#endif // CHARTWIDGET_H
 
