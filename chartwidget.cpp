#include "chartwidget.h"
#include <vector>
#include <string>
#include <math.h>
#include <sstream>
#include <algorithm>
#include "qchartviewer.h"
#include "logdata.h"
#include <QDebug>

using namespace std;

ChartWidget::ChartWidget(QWidget *parent, int r, int c, QList<int> list) : QWidget(parent), l(list), delt(1.0)
{
    w = 1610 / (c+1);
    h = 980 / (r+1);

    // Chart Viewer

    m_viewer = new QChartViewer(this);
    m_viewer->setGeometry(0, 0, w, h);

    connect(m_viewer, SIGNAL(viewPortChanged()), SLOT(onViewPortChanged()));
    connect(m_viewer, SIGNAL(mouseMovePlotArea(QMouseEvent*)), SLOT(onMouseMovePlotArea(QMouseEvent*)));
    connect(m_viewer, &QChartViewer::clicked, [=](){
        emit mouseClick(delt);
    });

    m_ViewPortControl = new QViewPortControl(this);
    m_ViewPortControl->setGeometry(0, h-100, w, 100);

    //
    // Load the data
    //

    m_timeStamps = DoubleArray(&LogData::instance()->lineX.first(), LogData::instance()->lineX.length());
    m_dataSeries_vehicle_vxy = DoubleArray(&LogData::instance()->data_vehicle_vxy.first(), LogData::instance()->data_vehicle_vxy.length());
    m_dataSeries_vehicle_ax = DoubleArray(&LogData::instance()->data_vehicle_ax.first(), LogData::instance()->data_vehicle_ax.length());
    m_dataSeries_vehicle_yawrate = DoubleArray(&LogData::instance()->data_vehicle_yawrate.first(), LogData::instance()->data_vehicle_yawrate.length());
    m_dataSeries_record_vxy = DoubleArray(&LogData::instance()->data_record_vxy.first(), LogData::instance()->data_record_vxy.length());
    m_dataSeries_record_ax = DoubleArray(&LogData::instance()->data_record_ax.first(), LogData::instance()->data_record_ax.length());
    m_dataSeries_record_yawrate = DoubleArray(&LogData::instance()->data_record_yawrate.first(), LogData::instance()->data_record_yawrate.length());
    m_dataSeries_front_wheel_angle = DoubleArray(&LogData::instance()->data_front_wheel_angle.first(), LogData::instance()->data_front_wheel_angle.length());
    m_dataSeries_record_wheel_angle = DoubleArray(&LogData::instance()->data_record_wheel_angle.first(), LogData::instance()->data_record_wheel_angle.length());

    if(!LogData::instance()->back_collision_ibeoX.isEmpty())
        m_back_collision_ibeoX = DoubleArray(&LogData::instance()->back_collision_ibeoX.first(), LogData::instance()->back_collision_ibeoX.length());
    if(!LogData::instance()->front_collision_ibeoX.isEmpty())
        m_front_collision_ibeoX = DoubleArray(&LogData::instance()->front_collision_ibeoX.first(), LogData::instance()->front_collision_ibeoX.length());
    if(!LogData::instance()->back_collision_fusionX.isEmpty())
        m_back_collision_fusionX = DoubleArray(&LogData::instance()->back_collision_fusionX.first(), LogData::instance()->back_collision_fusionX.length());
    if(!LogData::instance()->front_collision_fusionX.isEmpty())
        m_front_collision_fusionX = DoubleArray(&LogData::instance()->front_collision_fusionX.first(), LogData::instance()->front_collision_fusionX.length());
    if(!LogData::instance()->cutin_collision_riskX.isEmpty())
        m_cutin_collision_riskX = DoubleArray(&LogData::instance()->cutin_collision_riskX.first(), LogData::instance()->cutin_collision_riskX.length());
    if(!LogData::instance()->rear_end_collision_riskX.isEmpty())
        m_rear_end_collision_riskX = DoubleArray(&LogData::instance()->rear_end_collision_riskX.first(), LogData::instance()->rear_end_collision_riskX.length());
    if(!LogData::instance()->gapX.isEmpty())
        m_gapX = DoubleArray(&LogData::instance()->gapX.first(), LogData::instance()->gapX.length());
    if(!LogData::instance()->start_timestampX.isEmpty())
        m_start_timestampX = DoubleArray(&LogData::instance()->start_timestampX.first(), LogData::instance()->start_timestampX.length());
    if(!LogData::instance()->footfault_hdmapX.isEmpty())
        m_footfault_hdmapX = DoubleArray(&LogData::instance()->footfault_hdmapX.first(), LogData::instance()->footfault_hdmapX.length());
    if(!LogData::instance()->footfault_dectectX.isEmpty())
        m_footfault_dectectX = DoubleArray(&LogData::instance()->footfault_dectectX.first(), LogData::instance()->footfault_dectectX.length());
    if(!LogData::instance()->acc_differenceX.isEmpty())
        m_acc_differenceX = DoubleArray(&LogData::instance()->acc_differenceX.first(), LogData::instance()->acc_differenceX.length());
    if(!LogData::instance()->angle_differenceX.isEmpty())
        m_angle_differenceX = DoubleArray(&LogData::instance()->angle_differenceX.first(), LogData::instance()->angle_differenceX.length());
    if(!LogData::instance()->take_over_requestX.isEmpty())
        m_take_over_requestX = DoubleArray(&LogData::instance()->take_over_requestX.first(), LogData::instance()->take_over_requestX.length());
    if(!LogData::instance()->quit_take_overX.isEmpty())
        m_quit_take_overX = DoubleArray(&LogData::instance()->quit_take_overX.first(), LogData::instance()->quit_take_overX.length());

    if(!LogData::instance()->back_collision_ibeoY.isEmpty())
        m_back_collision_ibeoY = DoubleArray(&LogData::instance()->back_collision_ibeoY.first(), LogData::instance()->back_collision_ibeoY.length());
    if(!LogData::instance()->front_collision_ibeoY.isEmpty())
        m_front_collision_ibeoY = DoubleArray(&LogData::instance()->front_collision_ibeoY.first(), LogData::instance()->front_collision_ibeoY.length());
    if(!LogData::instance()->back_collision_fusionY.isEmpty())
        m_back_collision_fusionY = DoubleArray(&LogData::instance()->back_collision_fusionY.first(), LogData::instance()->back_collision_fusionY.length());
    if(!LogData::instance()->front_collision_fusionY.isEmpty())
        m_front_collision_fusionY = DoubleArray(&LogData::instance()->front_collision_fusionY.first(), LogData::instance()->front_collision_fusionY.length());
    if(!LogData::instance()->cutin_collision_riskY.isEmpty())
        m_cutin_collision_riskY = DoubleArray(&LogData::instance()->cutin_collision_riskY.first(), LogData::instance()->cutin_collision_riskY.length());
    if(!LogData::instance()->rear_end_collision_riskY.isEmpty())
        m_rear_end_collision_riskY = DoubleArray(&LogData::instance()->rear_end_collision_riskY.first(), LogData::instance()->rear_end_collision_riskY.length());
    if(!LogData::instance()->gapY.isEmpty())
        m_gapY = DoubleArray(&LogData::instance()->gapY.first(), LogData::instance()->gapY.length());
    if(!LogData::instance()->start_timestampY.isEmpty())
        m_start_timestampY = DoubleArray(&LogData::instance()->start_timestampY.first(), LogData::instance()->start_timestampY.length());
    if(!LogData::instance()->footfault_hdmapY.isEmpty())
        m_footfault_hdmapY = DoubleArray(&LogData::instance()->footfault_hdmapY.first(), LogData::instance()->footfault_hdmapY.length());
    if(!LogData::instance()->footfault_dectectY.isEmpty())
        m_footfault_dectectY = DoubleArray(&LogData::instance()->footfault_dectectY.first(), LogData::instance()->footfault_dectectY.length());
    if(!LogData::instance()->acc_differenceY.isEmpty())
        m_acc_differenceY = DoubleArray(&LogData::instance()->acc_differenceY.first(), LogData::instance()->acc_differenceY.length());
    if(!LogData::instance()->angle_differenceY.isEmpty())
        m_angle_differenceY = DoubleArray(&LogData::instance()->angle_differenceY.first(), LogData::instance()->angle_differenceY.length());
    if(!LogData::instance()->take_over_requestY.isEmpty())
        m_take_over_requestY = DoubleArray(&LogData::instance()->take_over_requestY.first(), LogData::instance()->take_over_requestY.length());
    if(!LogData::instance()->quit_take_overY.isEmpty())
        m_quit_take_overY = DoubleArray(&LogData::instance()->quit_take_overY.first(), LogData::instance()->quit_take_overY.length());

    //
    // Initialize the QChartViewer
    //

    // Set the full x range to be the duration of the data
    m_viewer->setFullRange("x", m_timeStamps[0], m_timeStamps[m_timeStamps.len - 1]);

    // Initialize the view port to show the latest 20% of the time range
    m_viewer->setViewPortWidth(1);
    m_viewer->setViewPortLeft(1 - m_viewer->getViewPortWidth());

    m_viewer->setMouseUsage(Chart::MouseUsageScroll);

    // Trigger the ViewPortChanged event to draw the chart
    m_viewer->updateViewPort(true, true);

    //
    // Draw and display the full chart in the CViewPortControl
    //

    // Create an XYChart object of size w x h pixels
    down_chart = new XYChart(w,100);

    // Set the plotarea with the same horizontal position as that in the main chart for alignment.
    down_chart->setPlotArea(55, 10, w-70, 60, 0xc0d8ff, -1, 0x888888, Chart::Transparent, 0xffffff);

    // Set the x axis stem to transparent and the label font to 10pt Arial
    down_chart->xAxis()->setColors(Chart::Transparent);
    down_chart->xAxis()->setLabelStyle("arial.ttf", 10);

    // Set the y axis stem and labels to transparent (that is, hide the labels)
    down_chart->yAxis()->setColors(Chart::Transparent, Chart::Transparent);

    // Add a line layer for the lines with fast line mode enabled
    downLayer = down_chart->addLineLayer();
    downLayer->setFastLineMode();
    downLayer->setXData(m_timeStamps);

    if(l.contains(0))
    {
        downLayer->addDataSet(m_dataSeries_vehicle_vxy, 0x0072BD);
    }
    if(l.contains(1))
    {
        downLayer->addDataSet(m_dataSeries_vehicle_ax, 0xD95319);
    }
    if(l.contains(2))
    {
        downLayer->addDataSet(m_dataSeries_vehicle_yawrate, 0xEDB120);
    }
    if(l.contains(3))
    {
        downLayer->addDataSet(m_dataSeries_record_vxy, 0x7E2F8E);
    }
    if(l.contains(4))
    {
        downLayer->addDataSet(m_dataSeries_record_ax, 0x77AC30);
    }
    if(l.contains(5))
    {
        downLayer->addDataSet(m_dataSeries_record_yawrate, 0x4DBEEE);
    }
    if(l.contains(6))
    {
        downLayer->addDataSet(m_dataSeries_front_wheel_angle, 0xA2142F);
    }
    if(l.contains(7))
    {
        downLayer->addDataSet(m_dataSeries_record_wheel_angle, 0xff3333);
    }
    if(l.contains(8) && !LogData::instance()->back_collision_ibeoX.isEmpty())
    {
        down_chart->addScatterLayer(m_back_collision_ibeoX, m_back_collision_ibeoY);
    }
    if(l.contains(9) && !LogData::instance()->front_collision_ibeoX.isEmpty())
    {
        down_chart->addScatterLayer(m_front_collision_ibeoX, m_front_collision_ibeoY);
    }
    if(l.contains(10) && !LogData::instance()->back_collision_fusionX.isEmpty())
    {
        down_chart->addScatterLayer(m_back_collision_fusionX, m_back_collision_fusionY);
    }
    if(l.contains(11) && !LogData::instance()->front_collision_fusionX.isEmpty())
    {
        down_chart->addScatterLayer(m_front_collision_fusionX, m_front_collision_fusionY);
    }
    if(l.contains(12) && !LogData::instance()->cutin_collision_riskX.isEmpty())
    {
        down_chart->addScatterLayer(m_cutin_collision_riskX, m_cutin_collision_riskY);
    }
    if(l.contains(13) && !LogData::instance()->rear_end_collision_riskX.isEmpty())
    {
        down_chart->addScatterLayer(m_rear_end_collision_riskX, m_rear_end_collision_riskY);
    }
    if(l.contains(14) && !LogData::instance()->gapX.isEmpty())
    {
        down_chart->addScatterLayer(m_gapX, m_gapY);
    }
    if(l.contains(15) && !LogData::instance()->start_timestampX.isEmpty())
    {
        down_chart->addScatterLayer(m_start_timestampX, m_start_timestampY);
    }
    if(l.contains(16) && !LogData::instance()->footfault_hdmapX.isEmpty())
    {
        down_chart->addScatterLayer(m_footfault_hdmapX, m_footfault_hdmapY);
    }
    if(l.contains(17) && !LogData::instance()->footfault_dectectX.isEmpty())
    {
        down_chart->addScatterLayer(m_footfault_dectectX, m_footfault_dectectY);
    }
    if(l.contains(18) && !LogData::instance()->acc_differenceX.isEmpty())
    {
        down_chart->addScatterLayer(m_acc_differenceX, m_acc_differenceY);
    }
    if(l.contains(19) && !LogData::instance()->angle_differenceX.isEmpty())
    {
        down_chart->addScatterLayer(m_angle_differenceX, m_angle_differenceY);
    }
    if(l.contains(20) && !LogData::instance()->take_over_requestX.isEmpty())
    {
        down_chart->addScatterLayer(m_take_over_requestX, m_take_over_requestY);
    }
    if(l.contains(21) && !LogData::instance()->quit_take_overX.isEmpty())
    {
        down_chart->addScatterLayer(m_quit_take_overX, m_quit_take_overY);
    }

    // The x axis scales should reflect the full range of the view port
    down_chart->xAxis()->setDateScale(m_viewer->getValueAtViewPort("x", 0), m_viewer->getValueAtViewPort("x", 1));

    // For the automatic x-axis labels, set the minimum spacing to 75 pixels.
    down_chart->xAxis()->setTickDensity(75);

    // For the auto-scaled y-axis, as we hide the labels, we can disable axis rounding. This can
    // make the axis scale fit the data tighter.
    down_chart->yAxis()->setRounding(false, false);

    // Output the chart
    m_ViewPortControl->setChart(down_chart);

    //
    // Bind the CChartViewer to the CViewPortControl
    //
    m_ViewPortControl->setViewer(m_viewer);

    // Set the maximum zoom to 10 points
    m_viewer->setZoomInWidthLimit(10.0 / LogData::instance()->lineX.length());
    m_viewer->setMouseWheelZoomRatio(1.1);
    m_viewer->show();
}

//
// The ViewPortChanged event handler. This event occurs if the user scrolls or zooms in
// or out the chart by dragging or clicking on the chart. It can also be triggered by
// calling WinChartViewer.updateViewPort.
//
void ChartWidget::onViewPortChanged()
{
    // Update chart if necessary
    if (m_viewer->needUpdateChart())
    {
        //
        // Draw the chart and display it in the given viewer
        //

        // Get the start date and end date that are visible on the chart.
        double viewPortStartDate = m_viewer->getValueAtViewPort("x", m_viewer->getViewPortLeft());
        double viewPortEndDate = m_viewer->getValueAtViewPort("x", m_viewer->getViewPortLeft() + m_viewer->getViewPortWidth());

        // Get the array indexes that corresponds to the visible start and end dates
        int startIndex = (int)floor(Chart::bSearch(m_timeStamps, viewPortStartDate));
        int endIndex = (int)ceil(Chart::bSearch(m_timeStamps, viewPortEndDate));
        int noOfPoints = endIndex - startIndex + 1;

        // Extract the part of the data array that are visible.
        DoubleArray viewPortTimeStamps = DoubleArray(m_timeStamps.data + startIndex, noOfPoints);
        viewPortDataSeries_vehicle_vxy = DoubleArray(m_dataSeries_vehicle_vxy.data + startIndex, noOfPoints);
        viewPortDataSeries_vehicle_ax = DoubleArray(m_dataSeries_vehicle_ax.data + startIndex, noOfPoints);
        viewPortDataSeries_vehicle_yawrate = DoubleArray(m_dataSeries_vehicle_yawrate.data + startIndex, noOfPoints);
        viewPortDataSeries_record_vxy = DoubleArray(m_dataSeries_record_vxy.data + startIndex, noOfPoints);
        viewPortDataSeries_record_ax = DoubleArray(m_dataSeries_record_ax.data + startIndex, noOfPoints);
        viewPortDataSeries_record_yawrate = DoubleArray(m_dataSeries_record_yawrate.data + startIndex, noOfPoints);
        viewPortDataSeries_front_wheel_angle = DoubleArray(m_dataSeries_front_wheel_angle.data + startIndex, noOfPoints);
        viewPortDataSeries_record_wheel_angle = DoubleArray(m_dataSeries_record_wheel_angle.data + startIndex, noOfPoints);

        int startIndex_back_collision = (int)floor(Chart::bSearch(m_back_collision_ibeoX, viewPortStartDate));
        int endIndex_back_collision = (int)ceil(Chart::bSearch(m_back_collision_ibeoX, viewPortEndDate));
        int noOfPoints_back_collision = endIndex_back_collision - startIndex_back_collision + 1;
        v_back_collision_ibeoX = DoubleArray(m_back_collision_ibeoX.data + startIndex_back_collision, noOfPoints_back_collision);
        v_back_collision_ibeoY = DoubleArray(m_back_collision_ibeoY.data + startIndex_back_collision, noOfPoints_back_collision);

        int startIndex_front_collision_ibeo = (int)floor(Chart::bSearch(m_front_collision_ibeoX, viewPortStartDate));
        int endIndex_front_collision_ibeo = (int)ceil(Chart::bSearch(m_front_collision_ibeoX, viewPortEndDate));
        int noOfPoints_front_collision_ibeo = endIndex_front_collision_ibeo - startIndex_front_collision_ibeo + 1;
        v_front_collision_ibeoX = DoubleArray(m_front_collision_ibeoX.data + startIndex_front_collision_ibeo, noOfPoints_front_collision_ibeo);
        v_front_collision_ibeoY = DoubleArray(m_front_collision_ibeoY.data + startIndex_front_collision_ibeo, noOfPoints_front_collision_ibeo);

        int startIndex_back_collision_fusion = (int)floor(Chart::bSearch(m_back_collision_fusionX, viewPortStartDate));
        int endIndex_back_collision_fusion = (int)ceil(Chart::bSearch(m_back_collision_fusionX, viewPortEndDate));
        int noOfPoints_back_collision_fusion = endIndex_back_collision_fusion - startIndex_back_collision_fusion + 1;
        v_back_collision_fusionX = DoubleArray(m_back_collision_fusionX.data + startIndex_back_collision_fusion, noOfPoints_back_collision_fusion);
        v_back_collision_fusionY = DoubleArray(m_back_collision_fusionY.data + startIndex_back_collision_fusion, noOfPoints_back_collision_fusion);

        int startIndex_front_collision_fusion = (int)floor(Chart::bSearch(m_front_collision_fusionX, viewPortStartDate));
        int endIndex_front_collision_fusion = (int)ceil(Chart::bSearch(m_front_collision_fusionX, viewPortEndDate));
        int noOfPoints_front_collision_fusion = endIndex_front_collision_fusion - startIndex_front_collision_fusion + 1;
        v_front_collision_fusionX = DoubleArray(m_front_collision_fusionX.data + startIndex_front_collision_fusion, noOfPoints_front_collision_fusion);
        v_front_collision_fusionY = DoubleArray(m_front_collision_fusionY.data + startIndex_front_collision_fusion, noOfPoints_front_collision_fusion);

        int startIndex_cutin_collision_risk = (int)floor(Chart::bSearch(m_cutin_collision_riskX, viewPortStartDate));
        int endIndex_cutin_collision_risk = (int)ceil(Chart::bSearch(m_cutin_collision_riskX, viewPortEndDate));
        int noOfPoints_cutin_collision_risk = endIndex_cutin_collision_risk - startIndex_cutin_collision_risk + 1;
        v_cutin_collision_riskX = DoubleArray(m_cutin_collision_riskX.data + startIndex_cutin_collision_risk, noOfPoints_cutin_collision_risk);
        v_cutin_collision_riskY = DoubleArray(m_cutin_collision_riskY.data + startIndex_cutin_collision_risk, noOfPoints_cutin_collision_risk);

        int startIndex_rear_end_collision_risk = (int)floor(Chart::bSearch(m_rear_end_collision_riskX, viewPortStartDate));
        int endIndex_rear_end_collision_risk = (int)ceil(Chart::bSearch(m_rear_end_collision_riskX, viewPortEndDate));
        int noOfPoints_rear_end_collision_risk = endIndex_rear_end_collision_risk - startIndex_rear_end_collision_risk + 1;
        v_rear_end_collision_riskX = DoubleArray(m_rear_end_collision_riskX.data + startIndex_rear_end_collision_risk, noOfPoints_rear_end_collision_risk);
        v_rear_end_collision_riskY = DoubleArray(m_rear_end_collision_riskY.data + startIndex_rear_end_collision_risk, noOfPoints_rear_end_collision_risk);

        // Get the array indexes that corresponds to the visible start and end dates
        int startIndex_gap = (int)floor(Chart::bSearch(m_gapX, viewPortStartDate));
        int endIndex_gap = (int)ceil(Chart::bSearch(m_gapX, viewPortEndDate));
        int noOfPoints_gap = endIndex_gap - startIndex_gap + 1;
        v_gapX = DoubleArray(m_gapX.data + startIndex_gap, noOfPoints_gap);
        v_gapY = DoubleArray(m_gapY.data + startIndex_gap, noOfPoints_gap);

        int startIndex_start_timestamp = (int)floor(Chart::bSearch(m_start_timestampX, viewPortStartDate));
        int endIndex_start_timestamp = (int)ceil(Chart::bSearch(m_start_timestampX, viewPortEndDate));
        int noOfPoints_start_timestamp = endIndex_start_timestamp - startIndex_start_timestamp + 1;
        v_start_timestampX = DoubleArray(m_start_timestampX.data + startIndex_start_timestamp, noOfPoints_start_timestamp);
        v_start_timestampY = DoubleArray(m_start_timestampY.data + startIndex_start_timestamp, noOfPoints_start_timestamp);

        int startIndex_footfault_hdmap = (int)floor(Chart::bSearch(m_footfault_hdmapX, viewPortStartDate));
        int endIndex_footfault_hdmap = (int)ceil(Chart::bSearch(m_footfault_hdmapX, viewPortEndDate));
        int noOfPoints_footfault_hdmap = endIndex_footfault_hdmap - startIndex_footfault_hdmap + 1;
        v_footfault_hdmapX = DoubleArray(m_footfault_hdmapX.data + startIndex_footfault_hdmap, noOfPoints_footfault_hdmap);
        v_footfault_hdmapY = DoubleArray(m_footfault_hdmapY.data + startIndex_footfault_hdmap, noOfPoints_footfault_hdmap);

        int startIndex_footfault_dectect = (int)floor(Chart::bSearch(m_footfault_dectectX, viewPortStartDate));
        int endIndex_footfault_dectect = (int)ceil(Chart::bSearch(m_footfault_dectectX, viewPortEndDate));
        int noOfPoints_footfault_dectect = endIndex_footfault_dectect - startIndex_footfault_dectect + 1;
        v_footfault_dectectX = DoubleArray(m_footfault_dectectX.data + startIndex_footfault_dectect, noOfPoints_footfault_dectect);
        v_footfault_dectectY = DoubleArray(m_footfault_dectectY.data + startIndex_footfault_dectect, noOfPoints_footfault_dectect);

        int startIndex_acc_difference = (int)floor(Chart::bSearch(m_acc_differenceX, viewPortStartDate));
        int endIndex_acc_difference = (int)ceil(Chart::bSearch(m_acc_differenceX, viewPortEndDate));
        int noOfPoints_acc_difference = endIndex_acc_difference - startIndex_acc_difference + 1;
        v_acc_differenceX = DoubleArray(m_acc_differenceX.data + startIndex_acc_difference, noOfPoints_acc_difference);
        v_acc_differenceY = DoubleArray(m_acc_differenceY.data + startIndex_acc_difference, noOfPoints_acc_difference);

        int startIndex_angle_difference = (int)floor(Chart::bSearch(m_angle_differenceX, viewPortStartDate));
        int endIndex_angle_difference = (int)ceil(Chart::bSearch(m_angle_differenceX, viewPortEndDate));
        int noOfPoints_angle_difference = endIndex_angle_difference - startIndex_angle_difference + 1;
        v_angle_differenceX = DoubleArray(m_angle_differenceX.data + startIndex_angle_difference, noOfPoints_angle_difference);
        v_angle_differenceY = DoubleArray(m_angle_differenceY.data + startIndex_angle_difference, noOfPoints_angle_difference);

        int startIndex_take_over_request = (int)floor(Chart::bSearch(m_take_over_requestX, viewPortStartDate));
        int endIndex_take_over_request = (int)ceil(Chart::bSearch(m_take_over_requestX, viewPortEndDate));
        int noOfPoints_take_over_request = endIndex_take_over_request - startIndex_take_over_request + 1;
        v_take_over_requestX = DoubleArray(m_take_over_requestX.data + startIndex_take_over_request, noOfPoints_take_over_request);
        v_take_over_requestY = DoubleArray(m_take_over_requestY.data + startIndex_take_over_request, noOfPoints_take_over_request);

        int startIndex_quit_take_over = (int)floor(Chart::bSearch(m_quit_take_overX, viewPortStartDate));
        int endIndex_quit_take_over = (int)ceil(Chart::bSearch(m_quit_take_overX, viewPortEndDate));
        int noOfPoints_quit_take_over = endIndex_quit_take_over - startIndex_quit_take_over + 1;
        v_quit_take_overX = DoubleArray(m_quit_take_overX.data + startIndex_quit_take_over, noOfPoints_quit_take_over);
        v_quit_take_overY = DoubleArray(m_quit_take_overY.data + startIndex_quit_take_over, noOfPoints_quit_take_over);

        ///////////////////////////////////////////////////////////////////////////////////////
        // Configure overall chart appearance.
        ///////////////////////////////////////////////////////////////////////////////////////

        // Create an XYChart object of size w x h pixels
        up_chart = new XYChart(w, h-100);

        // Set the plotarea at (55, 55) with width 80 pixels less than chart width, and height 92 pixels
        // less than chart height. Use a vertical gradient from light blue (f0f6ff) to sky blue (a0c0ff)
        // as background. Set border to transparent and grid lines to white (ffffff).
        up_chart->setPlotArea(55, 35, w-70, h-165);

        // As the data can lie outside the plotarea in a zoomed chart, we need enable clipping.
        up_chart->setClipping();

        // Set the x and y axis stems to transparent and the label font to 10pt Arial
        up_chart->xAxis()->setColors(Chart::Transparent);
        up_chart->yAxis()->setColors(Chart::Transparent);
        up_chart->xAxis()->setLabelStyle("arial.ttf", 10);
        up_chart->yAxis()->setLabelStyle("arial.ttf", 10);

        ///////////////////////////////////////////////////////////////////////////////////////
        // Add data to chart
        ///////////////////////////////////////////////////////////////////////////////////////
        upLayer = up_chart->addLineLayer();
        upLayer->setLineWidth(2);
        upLayer->setFastLineMode();
        upLayer->setXData(viewPortTimeStamps);

        if(l.contains(0))
        {
            upLayer->addDataSet(viewPortDataSeries_vehicle_vxy, 0x0072BD, "data_vehicle_vxy");
        }
        if(l.contains(1))
        {
            upLayer->addDataSet(viewPortDataSeries_vehicle_ax, 0xD95319, "data_vehicle_ax");
        }
        if(l.contains(2))
        {
            upLayer->addDataSet(viewPortDataSeries_vehicle_yawrate, 0xEDB120, "data_vehicle_yawrate");
        }
        if(l.contains(3))
        {
            upLayer->addDataSet(viewPortDataSeries_record_vxy, 0x7E2F8E, "data_record_vxy");
        }
        if(l.contains(4))
        {
            upLayer->addDataSet(viewPortDataSeries_record_ax, 0x77AC30, "data_record_ax");
        }
        if(l.contains(5))
        {
            upLayer->addDataSet(viewPortDataSeries_record_yawrate, 0x4DBEEE, "data_record_yawrate");
        }
        if(l.contains(6))
        {
            upLayer->addDataSet(viewPortDataSeries_front_wheel_angle, 0xA2142F, "data_front_wheel_angle");
        }
        if(l.contains(7))
        {
            upLayer->addDataSet(viewPortDataSeries_record_wheel_angle, 0xff3333, "data_record_wheel_angle");
        }

        if(l.contains(8) && !LogData::instance()->back_collision_ibeoX.isEmpty())
        {
            up_chart->addScatterLayer(v_back_collision_ibeoX, v_back_collision_ibeoY, "back_collision_ibeo");
        }
        if(l.contains(9) && !LogData::instance()->front_collision_ibeoX.isEmpty())
        {
            up_chart->addScatterLayer(v_front_collision_ibeoX, v_front_collision_ibeoY, "front_collision_ibeo");
        }
        if(l.contains(10) && !LogData::instance()->back_collision_fusionX.isEmpty())
        {
            up_chart->addScatterLayer(v_back_collision_fusionX, v_back_collision_fusionY, "back_collision_fusion");
        }
        if(l.contains(11) && !LogData::instance()->front_collision_fusionX.isEmpty())
        {
            up_chart->addScatterLayer(v_front_collision_fusionX, v_front_collision_fusionY, "front_collision_fusion");
        }
        if(l.contains(12) && !LogData::instance()->cutin_collision_riskX.isEmpty())
        {
            up_chart->addScatterLayer(v_cutin_collision_riskX, v_cutin_collision_riskY, "cutin_collision_risk");
        }
        if(l.contains(13) && !LogData::instance()->rear_end_collision_riskX.isEmpty())
        {
            up_chart->addScatterLayer(v_rear_end_collision_riskX, v_rear_end_collision_riskY, "rear_end_collision_risk");
        }
        if(l.contains(14) && !LogData::instance()->gapX.isEmpty())
        {
            up_chart->addScatterLayer(v_gapX, v_gapY, "gap");
        }
        if(l.contains(15) && !LogData::instance()->start_timestampX.isEmpty())
        {
            up_chart->addScatterLayer(v_start_timestampX, v_start_timestampY, "start_timestamp");
        }
        if(l.contains(16) && !LogData::instance()->footfault_hdmapX.isEmpty())
        {
            up_chart->addScatterLayer(v_footfault_hdmapX, v_footfault_hdmapY, "footfault_hdmap");
        }
        if(l.contains(17) && !LogData::instance()->footfault_dectectX.isEmpty())
        {
            up_chart->addScatterLayer(v_footfault_dectectX, v_footfault_dectectY, "footfault_dectect");
        }
        if(l.contains(18) && !LogData::instance()->acc_differenceX.isEmpty())
        {
            up_chart->addScatterLayer(v_acc_differenceX, v_acc_differenceY, "acc_difference");
        }
        if(l.contains(19) && !LogData::instance()->angle_differenceX.isEmpty())
        {
            up_chart->addScatterLayer(v_angle_differenceX, v_angle_differenceY, "angle_difference");
        }
        if(l.contains(20) && !LogData::instance()->take_over_requestX.isEmpty())
        {
            up_chart->addScatterLayer(v_take_over_requestX, v_take_over_requestY, "take_over_request");
        }
        if(l.contains(21) && !LogData::instance()->quit_take_overX.isEmpty())
        {
            up_chart->addScatterLayer(v_quit_take_overX, v_quit_take_overY, "quit_take_over");
        }

        ///////////////////////////////////////////////////////////////////////////////////////
        // Configure axis scale and labelling
        ///////////////////////////////////////////////////////////////////////////////////////

        // Set the x-axis as a date/time axis with the scale according to the view port x range.
        m_viewer->syncDateAxisWithViewPort("x", up_chart->xAxis());

        // For the automatic y-axis labels, set the minimum spacing to 30 pixels.
        up_chart->yAxis()->setTickDensity(30);

        ///////////////////////////////////////////////////////////////////////////////////////
        // Output the chart
        ///////////////////////////////////////////////////////////////////////////////////////

        // We need to update the track line too. If the mouse is moving on the chart (eg. if
        // the user drags the mouse on the chart to scroll it), the track line will be updated
        // in the MouseMovePlotArea event. Otherwise, we need to update the track line here.
        if (!m_viewer->isInMouseMoveEvent())
        {
            trackLineLegend(up_chart, (0 == m_viewer->getChart()) ? up_chart->getPlotArea()->getRightX() : m_viewer->getPlotAreaMouseX());
        }
        m_viewer->setChart(up_chart);
    }
}

//
// Draw track line with data labels
//
void ChartWidget::trackLineLegend(XYChart *c, int mouseX)
{
    // Clear the current dynamic layer and get the DrawArea object to draw on it.
    DrawArea *d = c->initDynamicLayer();

    // The plot area object
    PlotArea *plotArea = c->getPlotArea();

    // Get the data x-value that is nearest to the mouse, and find its pixel coordinate.
    double xValue = c->getNearestXValue(mouseX);
    int xCoor = c->getXCoor(xValue);

    // Draw a vertical track line at the x-position
    d->vline(plotArea->getTopY(), plotArea->getBottomY(), xCoor, 0xaaaaaa);

    delt = LogData::instance()->endTimeStamp - LogData::instance()->videoStamp.value(double(xValue));
    if(delt < 0)
    {
        delt = 0.0;
    }

    // Container to hold the legend entries
    vector<string> legendEntries;

    // Iterate through all layers to build the legend array
    for (int i = 0; i < c->getLayerCount(); ++i) {
        Layer *layer = c->getLayerByZ(i);

        // The data array index of the x-value
        int xIndex = layer->getXIndexOf(xValue);

        // Iterate through all the data sets in the layer
        for (int j = 0; j < layer->getDataSetCount(); ++j) {
            DataSet *dataSet = layer->getDataSetByZ(j);

            // We are only interested in visible data sets with names
            const char *dataName = dataSet->getDataName();
            int color = dataSet->getDataColor();
            if (dataName && *dataName && (color != Chart::Transparent)) {

                // Build the legend entry, consist of the legend icon, name and data value.
                double dataValue = dataSet->getValue(xIndex);
                ostringstream legendEntry;
                legendEntry << "<*block*>" << dataSet->getLegendIcon() << " " << dataName << ": " <<
                               ((dataValue == Chart::NoValue) ? "N/A" : c->formatValue(dataValue, "{value|P4}"))
                            << "<*/*>";
                legendEntries.push_back(legendEntry.str());


                // Draw a track dot for data points within the plot area
                int yCoor = c->getYCoor(dataSet->getPosition(xIndex), dataSet->getUseYAxis());
                if ((yCoor >= plotArea->getTopY()) && (yCoor <= plotArea->getBottomY())) {
                    d->circle(xCoor, yCoor, 5, 5, color, color);
                }
            }
        }
    }

    QString text = QString("Timestamp: ") + LogData::instance()->year_string + QString::number(qlonglong((xValue+LogData::instance()->beginTime)*1000000));
    QByteArray ba = text.toLatin1();
    const char *c_str2 = ba.data();

    // Create the legend by joining the legend entries
    ostringstream legendText;
    legendText << "<*block,maxWidth=" << plotArea->getWidth() << "*><*block*><*font=arialbd.ttf*>[" << c_str2 << "]<*/*>";
    for (int i = ((int)legendEntries.size()) - 1; i >= 0; --i)
    {
        legendText << "        " << legendEntries[i];
    }

    // Display the legend on the top of the plot area
    TTFText *t = d->text(legendText.str().c_str(), "arialbd.ttf", 10);
    t->draw(plotArea->getLeftX() + 5, plotArea->getTopY() - 3, 0x333333, Chart::BottomLeft);
    t->destroy();
}

void ChartWidget::onMouseMovePlotArea(QMouseEvent *)
{
    trackLineLegend((XYChart *)m_viewer->getChart(), m_viewer->getPlotAreaMouseX());
    m_viewer->updateDisplay();
}
