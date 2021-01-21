#ifndef THREAD_H
#define THREAD_H 1

#include <QThread>

class Thread: public QThread
{

    Q_OBJECT
public:
    explicit Thread(QObject *parent = 0, bool b = false);
    virtual void run(void);
    void updateProgress(int v){ emit valueChanged(v); }

    // if Stop = true, the thread will break
    // out of the loop, and will be disposed
    bool stop;

signals:
    // To communicate with Gui Thread
    // we need to emit a signal
    void valueChanged(int);

public slots:
    
};

#endif // THREAD_H