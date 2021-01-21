#ifndef THREAD_CPP
#define THREAD_CPP 1

#include "../../include/utils/thread.h"
#include <QtGui>

Thread::Thread(QObject *parent, bool b) :
                QThread(parent), stop(b)
{
}
    
void Thread::run()
{
    for(int i = 0; i <= 100; i++)
    {
        QMutex mutex;
        // evitar que outros tópicos alterem o valor "stop"
        mutex.lock();
        if(this->stop){ break; }
        mutex.unlock();

        // emite o sinal para a etiqueta de contagem
        emit valueChanged(i);

        this->msleep(500);
    }
}

#endif // THREAD_CPP