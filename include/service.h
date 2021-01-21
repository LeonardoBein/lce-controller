#ifndef SERVICE_H
#define SERVICE_H 1

#include "log/logApplication.h"
#include "utils/thread.h"

class Service: public Thread{
public:

    virtual void run(void){
        LogApplication::info("Iniciando");
        int error = this->main();
        if(error){
            LogApplication::info("Processo finalizado, mas com erro");
        }else{
            LogApplication::info("Processo finalizado");
        }
    }

    virtual int main(void) = 0;

    virtual ~Service(){}
};

#endif // SERVICE_H


