#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H 1

#include <QMainWindow>
#include "chart/chart.h"
#include "chart/chartView.h"
#include "../utils/dataset.h"

#include <QtCharts>


namespace Ui {
    class ChartWindow;
}

class ChartWindow: public QMainWindow
{
    Q_OBJECT

public:

    Chart* chart = nullptr;

    explicit ChartWindow(
                Chart* chart,
                QWidget* parent = nullptr,
                Dataset<double>* dataset = nullptr);
    ~ChartWindow();

public slots:

private slots:
    void on_actioncsv_triggered();

private:
    Dataset<double>* dataset;
    Ui::ChartWindow *ui;

};

#endif // CHARTWINDOW_H
