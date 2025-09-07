#include "mainwindow.h"

#include <QApplication>

#include "algorithms.h"
#include <QHBoxLayout>
#include <QtCharts/QChartView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QWidget* centralWidget = new QWidget(&w);
    QHBoxLayout* layout = new QHBoxLayout(centralWidget);

    Algorithms *algo = new Algorithms;
    simple_merge_test_case(algo);

    simple_matrix_test_case(algo);

    //BenchmarkResult results = compute_triplets(algo);

    BenchmarkResult results = compute_matrices(algo);

    QChartView* chartView = new QChartView(&w);
    QChartView* chartView2 = new QChartView(&w);

    results.test_names = {"Положительные числа", "Отрицательные числа", "Случайные числа"};
    setupChart(chartView, "Время выполнения (мксек)", results.test_names, results.durations);
    layout->addWidget(chartView);

    setupChart(chartView2, "Число операций", results.test_names, results.operations);
    layout->addWidget(chartView2);

    w.setCentralWidget(centralWidget);

    w.show();

    return a.exec();
}
