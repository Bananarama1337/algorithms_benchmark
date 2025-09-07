#include "mainwindow.h"
#include <QApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void setupChart(QChartView* chartView,
                const QString title,
                const QStringList& series_names,
                const QVector<QVector<QPointF>>& series_data)
{
    QChart* chart = new QChart();
    chart->legend()->show();
    QFont legendFont;
    legendFont.setPointSize(14);
    chart->legend()->setFont(legendFont);

    QValueAxis* axisX = new QValueAxis();
    QFont axisTitleFont;
    axisTitleFont.setPointSize(14);
    axisTitleFont.setBold(true);
    axisX->setTitleFont(axisTitleFont);
    axisX->setTitleText("Количество элементов");

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText(title);
    axisY->setTitleFont(axisTitleFont);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    for (int i = 0; i < series_names.size(); ++i) {
        QLineSeries* series = new QLineSeries();
        series->setName(series_names[i]);
        for (const QPointF& point : series_data[i]) {
            series->append(point);
        }
        chart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}
