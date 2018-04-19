#include "mainwindow.h"

#include "createtable.h"
#include "logdata.h"
#include "leftwidget.h"

#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QAction>
#include <QCheckBox>
#include <QFileDialog>
#include <QDebug>
#include <QPointF>
#include <QMenu>

#include <QtWebEngineWidgets/QWebEngineView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QToolBar *tool = new QToolBar(this);
    tool->setMovable(false);

    //load log file
    QAction *action1 = tool->addAction("load...");
    connect(action1, &QAction::triggered, [=](){
        LogData::instance()->fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "./", tr("log (*.log)"));
        LogData::instance()->setupSeries();
        if(!LogData::instance()->fileName.isEmpty())
        {
            left->setEnabled(true);
        }
    });

    QAction *action2 = tool->addAction("charts");

    QWidget *widget = new QWidget(this); //zheng ti jie mian

    left = new QStackedWidget(this);
    left->setStyleSheet("background-color: rgb(165, 165, 165);");
    left->setFixedWidth(200);
    left->setDisabled(true);

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

    widget->setLayout(vLayout);
    setCentralWidget(widget);

    CreateTable *table = new CreateTable(this);
    table->hide();
    connect(action2, &QAction::triggered, [=](){
        table->move(50,30);
        table->show();
    });
    //set grid view
    connect(table, &CreateTable::showTable, [=](int row, int column){
        QList<QWebEngineView*> items = right->findChildren<QWebEngineView*>(QString());
        for(QWebEngineView *item : items)
        {
            delete item;
        }

        for (int i = 0; i <= row; ++i)
        {
            for (int j = 0; j <= column; ++j)
            {
                LeftWidget *leftWidget = new LeftWidget();
                left->addWidget(leftWidget);

                QWebEngineView *chartview = new QWebEngineView();
                chartview->setStyleSheet(("border:2px solid rgb(195, 195, 195)"));
                gridLayout->addWidget(chartview,i,j);
            }
        }
    });


    resize(800,600);
    setWindowTitle("Analyze");
}

MainWindow::~MainWindow()
{

}
