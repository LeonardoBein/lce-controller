#ifndef MAINWINDOW_CPP
#define MAINWINDOW_CPP 1

#include "../../../include/gui/mainWindow.h"
#include "uiMainWindow.h"
#include "../../../include/log/logApplication.h"
#include "../../../include/utils/time.h"
#include "../../modules/emissao_radiada.cpp"
#include "../../../include/utils/dataset.h"

#include <QtGui>

#define DEFAULT_START_FREQ 10000
#define DEFAULT_STOP_FREQ 20000
#define DEFAULT_STEP_ANGLE 45

MainWindow::MainWindow(QWidget *parent): 
                                QMainWindow(parent),
                                ui(new Ui::MainWindow),
                                service(new EmissaoRadiada(
                                                    DEFAULT_START_FREQ,
                                                    DEFAULT_STOP_FREQ,
                                                    DEFAULT_STEP_ANGLE))
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setMinimum(0);
    this->reset_values();

    connect( service, SIGNAL( valueChanged(int) ), ui->progressBar, SLOT( setValue(int) ) );
    connect( service , SIGNAL( finished() ), this, SLOT( stop_service() ));
    
}

void MainWindow::disable_widgets(void){
    this->ui->startButton->setDisabled(true);
    this->ui->resetButton->setDisabled(true);
    this->ui->start_freq->setDisabled(true);
    this->ui->stop_freq->setDisabled(true);
    this->ui->step_angle->setDisabled(true);
}

void MainWindow::enable_widgets(void){
    this->ui->startButton->setDisabled(false);
    this->ui->resetButton->setDisabled(false);
    this->ui->start_freq->setDisabled(false);
    this->ui->stop_freq->setDisabled(false);
    this->ui->step_angle->setDisabled(false);
}

void MainWindow::reset_values(void){
    this->ui->start_freq->setValue(DEFAULT_START_FREQ);
    ((EmissaoRadiada*)this->service)->setStartFrequency(DEFAULT_START_FREQ);
    this->ui->stop_freq->setValue(DEFAULT_STOP_FREQ);
    ((EmissaoRadiada*)this->service)->setStopFrequency(DEFAULT_STOP_FREQ);
    this->ui->step_angle->setValue(DEFAULT_STEP_ANGLE);
    ((EmissaoRadiada*)this->service)->setStepAngleFrequency(DEFAULT_STEP_ANGLE);
}

void MainWindow::stop_service(void){
    this->enable_widgets();

    QLineSeries *series = new QLineSeries();
    Dataset<double>* dataset = new Dataset<double>("time","position", NULL); 
    series->setUseOpenGL(true);
    for (int i = 0; i < 1000; i++) {
        QPointF p((qreal) i, qLn((qreal)i));
        *series << p;
        dataset->addRow((double)i,(double)qLn((qreal)i));
    }

    scheen = new ChartWindow(new Chart(), this, dataset);
    scheen->chart->legend()->hide();
    scheen->chart->setTitle("TESTE");
    scheen->chart->addSeries(series);
    
    series->attachAxis(scheen->chart->m_axisX);
    series->attachAxis(scheen->chart->m_axisY);
    
    scheen->resize(420, 300);

    scheen->show();
}

void MainWindow::on_startButton_clicked()
{
    this->disable_widgets();
    ((EmissaoRadiada*)this->service)->start();
    // this->updateProgress((int)ui->progressBar->value()+1);
}

void MainWindow::on_resetButton_clicked()
{
    this->reset_values();
}

void MainWindow::on_start_freq_valueChanged(int arg1){
    ((EmissaoRadiada*)this->service)->setStartFrequency(arg1);
}

void MainWindow::on_stop_freq_valueChanged(int arg1){
    ((EmissaoRadiada*)this->service)->setStopFrequency(arg1);
}

void MainWindow::on_step_angle_valueChanged(int arg1){
    ((EmissaoRadiada*)this->service)->setStepAngleFrequency(arg1);
}

MainWindow::~MainWindow()
{
    service->exit();
    service->wait();
    delete ui;
    delete (EmissaoRadiada*)service;
    delete scheen;
}

#endif // MAINWINDOW_CPP
