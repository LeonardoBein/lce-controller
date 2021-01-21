#ifndef CHART_H
#define CHART_H 1

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>

QT_BEGIN_NAMESPACE
class QGestureEvent;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

//![1]
class Chart : public QChart
//![1]
{
public:
    QLogValueAxis* m_axisX;
    QValueAxis* m_axisY;


    explicit Chart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = {});    
    ~Chart();

protected:
    bool sceneEvent(QEvent *event);

private:
    bool gestureEvent(QGestureEvent *event);
   

private:

};

#endif // CHART_H