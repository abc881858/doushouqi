#include "mainwindow.h"
#include <QAction>
#include <QCheckBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMenu>
#include <QPointF>
#include <QScrollArea>
#include <QSize>
#include <QToolBar>
#include <QVBoxLayout>
#include "chartwidget.h"
#include "createtable.h"
#include "duration.h"
#include "leftwidget.h"
#include "logdata.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_duration(0)
{
    // tool bar
    QToolBar *tool = new QToolBar(this);
    tool->setMovable(false);

    // load log file
    QAction *loadLogAction = tool->addAction("load...");

    // show CreateTable
    QAction *chartViewAction = tool->addAction("charts");
    chartViewAction->setDisabled(true);

    connect(loadLogAction, &QAction::triggered, [=](){
        LogData::instance()->fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "./", tr("log (*.log)"));

        if(!LogData::instance()->fileName.isEmpty())
        {
            LogData::instance()->setupSeries();
            leftStack->setEnabled(true);
            chartViewAction->setEnabled(true);
        }
    });

    QAction *loadMediaAction = tool->addAction("load media...");

    QAction *action3 = tool->addAction("zoom picture");
    connect(action3, &QAction::triggered, [=](){
        dialog->show();
    });

    QWidget *mainWidget = new QWidget(this); //zheng ti jie mian

    left = new QWidget(this);
    left->setFixedWidth(200);

    leftStack = new QStackedWidget(left);
    leftStack->setStyleSheet("background-color: rgb(165, 165, 165);");
    leftStack->setFixedWidth(200);

    dialog = new QDialog(0);
    dialog->setFixedSize(1920,1080);
    QHBoxLayout *hlayout = new QHBoxLayout;

    m_preview = new QtAV::VideoPreviewWidget(dialog);
    QScrollArea *scroolarea = new QScrollArea(dialog);
    scroolarea->setWidget(m_preview);
    hlayout->addWidget(scroolarea);
    hlayout->setMargin(0);
    dialog->setLayout(hlayout);
    dialog->hide();

    connect(m_preview, &QtAV::VideoPreviewWidget::timestampChanged, [=](){
        pictureLabel->setPixmap(m_preview->grab().scaled(200,150));
        pictureLabel->update();
    });

    pictureLabel = new QLabel(left);
    pictureLabel->setFixedSize(200,150);
    pictureLabel->hide();

    connect(loadMediaAction, &QAction::triggered, [=](){
        QString file = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("Multimedia files(*)"));
        if (file.isEmpty())
        {
            return;
        }
        else
        {
            int secondTime = videoinfo_duration(file.toLatin1().data());
            m_duration = secondTime * 1000; // 后续精确到毫秒
            m_preview->setFile(file);
            m_preview->resize(1920,1080);
            m_preview->setTimestamp(3000);
            m_preview->preview();
            pictureLabel->show();
        }
    });

    vboxLayout = new QVBoxLayout;

    vboxLayout->addWidget(leftStack);
    vboxLayout->addWidget(pictureLabel);

    left->setLayout(vboxLayout);
    vboxLayout->setMargin(0);

    gridLayout = new QGridLayout;

    right = new QWidget(this);
    right->setStyleSheet("background-color: rgb(195, 195, 195);");
    right->setLayout(gridLayout);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(left);
    hLayout->addWidget(right);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(tool);
    vLayout->addLayout(hLayout);

    mainWidget->setLayout(vLayout);
    setCentralWidget(mainWidget);

    CreateTable *table = new CreateTable(this);
    table->hide();
    connect(chartViewAction, &QAction::triggered, [=](){
        table->move(50,30);
        table->show();
    });

    //set grid view
    connect(table, &CreateTable::showTable, [=](int row, int column){
        QList<ChartWidget*> items = right->findChildren<ChartWidget*>(QString());
        for(ChartWidget *item : items)
        {
            delete item;
        }

        for (int i = 0; i <= row; ++i)
        {
            for (int j = 0; j <= column; ++j)
            {
                LeftWidget *leftWidget = new LeftWidget(left);
                leftStack->addWidget(leftWidget);

                ChartWidget *chartview = new ChartWidget(right, row, column, leftWidget->list);
                chartview->setStyleSheet("background-color:white;");
                gridLayout->addWidget(chartview,i,j);
                connect(chartview, &ChartWidget::mouseClick, [=](double delt){
                    int stamp = m_duration - delt * 1000;
                    qDebug() << "current stamp" << m_duration << stamp;
                    if(stamp > 0)
                    {
                        m_preview->setTimestamp(stamp); //后续减少timeStamp次数 410967
                    }
                    else
                    {
                        m_preview->setTimestamp(0);
                    }
                    m_preview->preview();
                    leftStack->setCurrentWidget(leftWidget);
                });

                connect(leftWidget, &LeftWidget::openCheck, [=](int openID){
                    leftWidget->list.append(openID);
                    ChartWidget *cw = new ChartWidget(this, row, column, leftWidget->list);
                    gridLayout->replaceWidget(gridLayout->itemAtPosition(i, j)->widget(), cw);
                    connect(cw, &ChartWidget::mouseClick, [=](double delt){
                        int stamp = m_duration - delt * 1000;
                        qDebug() << "current stamp" << m_duration << stamp;
                        if(stamp > 0)
                        {
                            m_preview->setTimestamp(stamp); //后续减少timeStamp次数 410967
                        }
                        else
                        {
                            m_preview->setTimestamp(0);
                        }
                        m_preview->preview();
                        leftStack->setCurrentWidget(leftWidget);
                    });
                });

                connect(leftWidget, &LeftWidget::closeCheck, [=](int closeID){
                    leftWidget->list.removeOne(closeID);
                    ChartWidget *cw = new ChartWidget(this, row, column, leftWidget->list);
                    gridLayout->replaceWidget(gridLayout->itemAtPosition(i, j)->widget(), cw);
                    connect(cw, &ChartWidget::mouseClick, [=](double delt){
                        int stamp = m_duration - delt * 1000;
                        qDebug() << "current stamp" << m_duration << stamp;
                        if(stamp > 0)
                        {
                            m_preview->setTimestamp(stamp); //后续减少timeStamp次数 410967
                        }
                        else
                        {
                            m_preview->setTimestamp(0);
                        }
                        m_preview->preview();
                        leftStack->setCurrentWidget(leftWidget);
                    });
                });
            }
        }

    });

    resize(800,600);
    setWindowTitle("Log Viewer");
}

MainWindow::~MainWindow()
{

}
