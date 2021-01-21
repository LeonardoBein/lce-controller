#ifndef CHARTWINDOW_CPP
#define CHARTWINDOW_CPP 1

#include "../../../include/gui/chartWindow.h"
#include "uiChartWindow.h"
#include "../../../include/log/logApplication.h"
#include "../../../include/gui/chart/chart.h"
#include "../../../include/gui/chart/chartView.h"

#include <QtGui>
#include <QtCharts>

QT_CHARTS_USE_NAMESPACE

ChartWindow::ChartWindow(Chart* chart, QWidget *parent, Dataset<double>* dataset): 
                                QMainWindow(parent),
                                chart(chart),
                                dataset(dataset),
                                ui(new Ui::ChartWindow)
{
    ui->setupUi(this);

    
    // QObject::connect(this->ui->actioncsv, SIGNAL(changed()), this, SLOT(saveToFile()));

    // // Create chart, add data, hide legend, and add axis
    // Chart *chart = new Chart();
    // chart->legend()->hide();
    // chart->addSeries(series);
    // chart->createDefaultAxes();

    // // Customize the title font
    // QFont font;
    // font.setPixelSize(18);
    // chart->setTitleFont(font);
    // chart->setTitleBrush(QBrush(Qt::black));
    // chart->setTitle("Barry Bonds HRs as Pirate");

    // // Change the line color and weight
    // QPen pen(QRgb(0x000000));
    // pen.setWidth(2);
    // series->setPen(pen);

    // NoAnimation, GridAxisAnimations, SeriesAnimations
    // chart->setAnimationOptions(QChart::NoAnimation);

    ChartView *chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    
    this->setCentralWidget((QWidget*)chartView);
    this->grabGesture(Qt::PanGesture);
    this->grabGesture(Qt::PinchGesture);

    
}

ChartWindow::~ChartWindow()
{    
    delete chart;
    if(this->dataset){
        delete dataset;
    }
    delete ui;
}

void ChartWindow::on_actioncsv_triggered(){
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Salvar os pontos"),
    "",
    tr("Arquivo CSV (*.csv);;All Files (*)"));

    if(fileName.isEmpty()){
        return;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::information(this, tr("Impossível abrir o arquivo"), file.errorString());
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_5);
    out << this->dataset->exportCSV().c_str();
    
    
}

#endif // CHARTWINDOW_CPP
