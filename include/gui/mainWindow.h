#ifndef MAINWINDOW_H
#define MAINWINDOW_H 1

#include <QMainWindow>
#include "../service.h"
#include "chartWindow.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    void updateProgress(int v){ emit signalProgress(v); }
    ~MainWindow();
    

signals:
    void signalProgress(int);

public slots:

private slots:
    void on_start_freq_valueChanged(int arg1);
    void on_stop_freq_valueChanged(int arg1);
    void on_step_angle_valueChanged(int arg1);
    void on_startButton_clicked();
    void on_resetButton_clicked();
    void stop_service();
    

private:
    Ui::MainWindow *ui;
    Service* service;
    ChartWindow* scheen;
    
    void reset_values(void);

    void disable_widgets(void);
    void enable_widgets(void);

};

#endif // MAINWINDOW_H
