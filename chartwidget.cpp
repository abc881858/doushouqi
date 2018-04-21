#include "chartwidget.h"
#include "qchartviewer.h"
#include "logdata.h"
#include <vector>

ChartWidget::ChartWidget(QWidget *parent, int r, int c) : QWidget(parent)
{
    w = 1537 / (c+1);
    h = 1135 / (r+1);

    // Chart Viewer

    m_viewer = new QChartViewer(this);
    m_viewer->setGeometry(30, 20, w-70, h-100);

    connect(m_viewer, SIGNAL(viewPortChanged()), SLOT(onViewPortChanged()));
    connect(m_viewer, SIGNAL(mouseMovePlotArea(QMouseEvent*)), SLOT(onMouseMovePlotArea(QMouseEvent*)));

    m_ViewPortControl = new QViewPortControl(this);
    m_ViewPortControl->setGeometry(30, h-100, w-70, 70);

    //
    // Load the data
    //

    m_timeStamps = DoubleArray(&LogData::instance()->lineX.first(), LogData::instance()->lineX.length());
    m_dataSeriesA = DoubleArray(&LogData::instance()->data_vehicle_vxy.first(), LogData::instance()->data_vehicle_vxy.length());
//    m_dataSeriesB = DoubleArray(&LogData::instance()->data_vehicle_ax.first(), LogData::instance()->data_vehicle_ax.length());
//    m_dataSeriesC = DoubleArray(&LogData::instance()->data_vehicle_yawrate.first(), LogData::instance()->data_vehicle_yawrate.length());

    //
    // Initialize the QChartViewer
    //

    // Set the full x range to be the duration of the data
    m_viewer->setFullRange("x", m_timeStamps[0], m_timeStamps[m_timeStamps.len - 1]);

    // Initialize the view port to show the latest 20% of the time range
    m_viewer->setViewPortWidth(0.2);
    m_viewer->setViewPortLeft(1 - m_viewer->getViewPortWidth());

    // Set the maximum zoom to 10 points
    m_viewer->setZoomInWidthLimit(10.0 / m_timeStamps.len);
    m_viewer->setMouseWheelZoomRatio(1.1);

    // Trigger the ViewPortChanged event to draw the chart
    m_viewer->updateViewPort(true, true);

    //
    // Draw and display the full chart in the CViewPortControl
    //

    // Create an XYChart object of size w x h pixels
    m_chart = new XYChart(w-70,70);

    // Set the plotarea with the same horizontal position as that in the main chart for alignment.
    m_chart->setPlotArea(30, 20, w-70, h-150, 0xc0d8ff, -1, 0x888888, Chart::Transparent, 0xffffff);

    // Set the x axis stem to transparent and the label font to 10pt Arial
    m_chart->xAxis()->setColors(Chart::Transparent);
    m_chart->xAxis()->setLabelStyle("arial.ttf", 10);

    // Put the x-axis labels inside the plot area by setting a negative label gap. Use
    // setLabelAlignment to put the label at the right side of the tick.
    m_chart->xAxis()->setLabelGap(-1);
    m_chart->xAxis()->setLabelAlignment(1);

    // Set the y axis stem and labels to transparent (that is, hide the labels)
    m_chart->yAxis()->setColors(Chart::Transparent, Chart::Transparent);

    // Add a line layer for the lines with fast line mode enabled
    LineLayer *layer = m_chart->addLineLayer(m_dataSeriesA);
    layer->setFastLineMode();

    // Now we add the 3 data series to a line layer, using the color red (0xff3333), green
    // (0x008800) and blue (0x3333cc)
//    layer->setXData(m_timeStamps);
    layer->setXData(LogData::instance()->beginTime, LogData::instance()->endTime);

//    layer->addDataSet(m_dataSeriesA, 0xff3333);
//    layer->addDataSet(m_dataSeriesB, 0x008800);
//    layer->addDataSet(m_dataSeriesC, 0x3333cc);

    // The x axis scales should reflect the full range of the view port
    m_chart->xAxis()->setDateScale(m_viewer->getValueAtViewPort("x", 0), m_viewer->getValueAtViewPort("x", 1));

    // For the automatic x-axis labels, set the minimum spacing to 75 pixels.
    m_chart->xAxis()->setTickDensity(75);

    // For the auto-scaled y-axis, as we hide the labels, we can disable axis rounding. This can
    // make the axis scale fit the data tighter.
    m_chart->yAxis()->setRounding(false, false);

    // Output the chart
    m_ViewPortControl->setChart(m_chart);

    //
    // Bind the CChartViewer to the CViewPortControl
    //
    m_ViewPortControl->setViewer(m_viewer);




    // Initialize the view port to show the latest 20% of the time range
    m_viewer->setViewPortWidth(0.2);
    m_viewer->setViewPortLeft(1 - m_viewer->getViewPortWidth());

    // Set the maximum zoom to 10 points
    m_viewer->setZoomInWidthLimit(10.0 / LogData::instance()->lineX.length());
    m_viewer->setMouseWheelZoomRatio(1.1);

//    m_viewer->setChart(chart);

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
//        double viewPortStartDate = m_viewer->getValueAtViewPort("x", m_viewer->getViewPortLeft());
//        double viewPortEndDate = m_viewer->getValueAtViewPort("x", m_viewer->getViewPortLeft() + m_viewer->getViewPortWidth());

//        // Get the array indexes that corresponds to the visible start and end dates
//        int startIndex = (int)floor(Chart::bSearch(m_timeStamps, viewPortStartDate));
//        int endIndex = (int)ceil(Chart::bSearch(m_timeStamps, viewPortEndDate));
//        int noOfPoints = endIndex - startIndex + 1;

        // Extract the part of the data array that are visible.
//        DoubleArray viewPortTimeStamps = DoubleArray(m_timeStamps.data + startIndex, noOfPoints);
//        DoubleArray viewPortDataSeriesA = DoubleArray(m_dataSeriesA.data + startIndex, noOfPoints);
//        DoubleArray viewPortDataSeriesB = DoubleArray(m_dataSeriesB.data + startIndex, noOfPoints);
//        DoubleArray viewPortDataSeriesC = DoubleArray(m_dataSeriesC.data + startIndex, noOfPoints);

        //
        // At this stage, we have extracted the visible data. We can use those data to plot the chart.
        //

        ///////////////////////////////////////////////////////////////////////////////////////
        // Configure overall chart appearance.
        ///////////////////////////////////////////////////////////////////////////////////////

        // Create an XYChart object of size w x h pixels
        XYChart *m_chart = new XYChart(w-70, h-150);

        // Set the plotarea at (55, 55) with width 80 pixels less than chart width, and height 92 pixels
        // less than chart height. Use a vertical gradient from light blue (f0f6ff) to sky blue (a0c0ff)
        // as background. Set border to transparent and grid lines to white (ffffff).
        m_chart->setPlotArea(30, 20, w-70, h-150);
//                       m_chart->linearGradientColor(0, 55, 0, m_chart->getHeight() - 35, 0xf0f6ff, 0xa0c0ff),
//                       -1, Chart::Transparent, 0xffffff, 0xffffff);

        // As the data can lie outside the plotarea in a zoomed chart, we need enable clipping.
//        m_chart->setClipping();

//        // Add a title box using dark grey (0x333333) 15pt Arial Bold font
//        c->addTitle("   Zooming and Scrolling with Viewport Control", "arialbd.ttf", 15, 0x333333);

//        // Set legend icon style to use line style icon, sized for 10pt font
//        m_chart->getLegend()->setLineStyleKey();
//        m_chart->getLegend()->setFontSize(10);

        // Set the x and y axis stems to transparent and the label font to 10pt Arial
//        m_chart->xAxis()->setColors(Chart::Transparent);
//        m_chart->yAxis()->setColors(Chart::Transparent);
//        m_chart->xAxis()->setLabelStyle("arial.ttf", 10);
//        m_chart->yAxis()->setLabelStyle("arial.ttf", 10);

//        // Add axis title using 10pt Arial Bold font
//        c->yAxis()->setTitle("Ionic Temperature (C)", "arialbd.ttf", 10);

        ///////////////////////////////////////////////////////////////////////////////////////
        // Add data to chart
        ///////////////////////////////////////////////////////////////////////////////////////

        //
        // In this example, we represent the data by lines. You may modify the code below to use other
        // representations (areas, scatter plot, etc).
        //

        // Add a line layer for the lines, using a line width of 2 pixels
        LineLayer *layer = m_chart->addLineLayer(m_dataSeriesA);
        layer->setLineWidth(2);

        // In this demo, we do not have too many data points. In real code, the chart may contain a lot
        // of data points when fully zoomed out - much more than the number of horizontal pixels in this
        // plot area. So it is a good idea to use fast line mode.
        layer->setFastLineMode();

        // Now we add the 3 data series to a line layer, using the color red (0xff3333), green
        // (0x008800) and blue (0x3333cc)
//        layer->setXData(viewPortTimeStamps);
        layer->setXData(LogData::instance()->beginTime, LogData::instance()->endTime);
//        layer->addDataSet(viewPortDataSeriesA, 0xff3333, "Alpha");
//        layer->addDataSet(viewPortDataSeriesB, 0x008800, "Beta");
//        layer->addDataSet(viewPortDataSeriesC, 0x3333cc, "Gamma");

        ///////////////////////////////////////////////////////////////////////////////////////
        // Configure axis scale and labelling
        ///////////////////////////////////////////////////////////////////////////////////////

        // Set the x-axis as a date/time axis with the scale according to the view port x range.
//        m_viewer->syncDateAxisWithViewPort("x", m_chart->xAxis());

        // For the automatic y-axis labels, set the minimum spacing to 30 pixels.
//        m_chart->yAxis()->setTickDensity(30);

//        //
//        // In this demo, the time range can be from a few years to a few days. We demonstrate how to
//        // set up different date/time format based on the time range.
//        //

//        // If all ticks are yearly aligned, then we use "yyyy" as the label format.
//        m_chart->xAxis()->setFormatCondition("align", 360 * 86400);
//        m_chart->xAxis()->setLabelFormat("{value|yyyy}");

//        // If all ticks are monthly aligned, then we use "mmm yyyy" in bold font as the first
//        // label of a year, and "mmm" for other labels.
//        m_chart->xAxis()->setFormatCondition("align", 30 * 86400);
//        m_chart->xAxis()->setMultiFormat(Chart::StartOfYearFilter(), "<*font=bold*>{value|mmm<*br*>yyyy}", Chart::AllPassFilter(), "{value|mmm}");

//        // If all ticks are daily algined, then we use "mmm dd<*br*>yyyy" in bold font as the
//        // first label of a year, and "mmm dd" in bold font as the first label of a month, and
//        // "dd" for other labels.
//        m_chart->xAxis()->setFormatCondition("align", 86400);
//        m_chart->xAxis()->setMultiFormat(Chart::StartOfYearFilter(), "<*block,halign=left*><*font=bold*>{value|mmm dd<*br*>yyyy}", Chart::StartOfMonthFilter(), "<*font=bold*>{value|mmm dd}");
//        m_chart->xAxis()->setMultiFormat(Chart::AllPassFilter(), "{value|dd}");

//        // For all other cases (sub-daily ticks), use "hh:nn<*br*>mmm dd" for the first label of
//        // a day, and "hh:nn" for other labels.
//        m_chart->xAxis()->setFormatCondition("else");
//        m_chart->xAxis()->setMultiFormat(Chart::StartOfDayFilter(), "<*font=bold*>{value|hh:nn<*br*>mmm dd}", Chart::AllPassFilter(), "{value|hh:nn}");

        ///////////////////////////////////////////////////////////////////////////////////////
        // Output the chart
        ///////////////////////////////////////////////////////////////////////////////////////

        // We need to update the track line too. If the mouse is moving on the chart (eg. if
        // the user drags the mouse on the chart to scroll it), the track line will be updated
        // in the MouseMovePlotArea event. Otherwise, we need to update the track line here.
        if (!m_viewer->isInMouseMoveEvent())
        {
            trackLineLegend(m_chart, (0 == m_viewer->getChart()) ? m_chart->getPlotArea()->getRightX() : m_viewer->getPlotAreaMouseX());
        }
        delete m_viewer->getChart();
        m_viewer->setChart(m_chart);
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

//    // Container to hold the legend entries
//    vector<string> legendEntries;

//    // Iterate through all layers to build the legend array
//    for (int i = 0; i < c->getLayerCount(); ++i) {
//        Layer *layer = c->getLayerByZ(i);

//        // The data array index of the x-value
//        int xIndex = layer->getXIndexOf(xValue);

//        // Iterate through all the data sets in the layer
//        for (int j = 0; j < layer->getDataSetCount(); ++j) {
//            DataSet *dataSet = layer->getDataSetByZ(j);

//            // We are only interested in visible data sets with names
//            const char *dataName = dataSet->getDataName();
//            int color = dataSet->getDataColor();
//            if (dataName && *dataName && (color != Chart::Transparent)) {
//                // Build the legend entry, consist of the legend icon, name and data value.
//                double dataValue = dataSet->getValue(xIndex);
//                ostringstream legendEntry;
//                legendEntry << "<*block*>" << dataSet->getLegendIcon() << " " << dataName << ": " <<
//                    ((dataValue == Chart::NoValue) ? "N/A" : c->formatValue(dataValue, "{value|P4}"))
//                    << "<*/*>";
//                legendEntries.push_back(legendEntry.str());

//                // Draw a track dot for data points within the plot area
//                int yCoor = c->getYCoor(dataSet->getPosition(xIndex), dataSet->getUseYAxis());
//                if ((yCoor >= plotArea->getTopY()) && (yCoor <= plotArea->getBottomY())) {
//                    d->circle(xCoor, yCoor, 5, 5, color, color);
//                }
//            }
//        }
//    }

//    // Create the legend by joining the legend entries
//    ostringstream legendText;
//    legendText << "<*block,maxWidth=" << plotArea->getWidth() << "*><*block*><*font=arialbd.ttf*>["
//        << c->xAxis()->getFormattedLabel(xValue, "mm/dd/yyyy") << "]<*/*>";
//    for (int i = ((int)legendEntries.size()) - 1; i >= 0; --i)
//        legendText << "        " << legendEntries[i];

//    // Display the legend on the top of the plot area
//    TTFText *t = d->text(legendText.str().c_str(), "arialbd.ttf", 10);
//    t->draw(plotArea->getLeftX() + 5, plotArea->getTopY() - 3, 0x333333, Chart::BottomLeft);
//    t->destroy();
}


void ChartWidget::onMouseMovePlotArea(QMouseEvent *)
{
    int mouseX = m_viewer->getPlotAreaMouseX();

    // Clear the current dynamic layer and get the DrawArea object to draw on it.
    DrawArea *d = m_chart->initDynamicLayer();

    // The plot area object
    PlotArea *plotArea = m_chart->getPlotArea();

    // Get the data x-value that is nearest to the mouse, and find its pixel coordinate.
    double xValue = m_chart->getNearestXValue(mouseX);
    int xCoor = m_chart->getXCoor(xValue);
    // Draw a vertical track line at the x-position
    d->vline(plotArea->getTopY(), plotArea->getBottomY(), xCoor, 0xaaaaaa);

    m_viewer->updateDisplay();
}
