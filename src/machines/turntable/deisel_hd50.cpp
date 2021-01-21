#ifndef _DeiselHD50_APPLICATION
#define _DeiselHD50_APPLICATION 1

#include "../../../include/machine/turntable.h"
#include "../../../include/connection/gpib.h"
#include "../../../include/utils/parser.h"
#include <string>
#include <stdio.h>





class DeiselHD50: public Turntable{

private:

    std::string _addr;
    GPIB* _connection;
    
public:
    DeiselHD50(char* addr){
        this->_addr = addr;
        this->_connection = new GPIB(addr);
        
        this->_connection->setTestResponse(true);
        this->_connection->setTestWrite(true);
    }

    

    virtual void Reset(void){

    }
    
    virtual bool CheckStatus(float targetValue){
        float current_position = this->GetPosition();

        if (targetValue - 2 <= current_position  && current_position <= targetValue + 2){
            return true;
        }
        return false;
    }

    virtual std::vector<int> GetLimits(void){
        std::vector<int> v = { 360, 0 };
        return v;
    }

    virtual float GetPosition(void){
        char* buffer = this->_connection->query((char*) "CP", (char*)"45");
        return Parser::Float(buffer);
    }


    virtual void SetPosition(float position){
        std::vector<int> limits = this->GetLimits();

        if (position < limits[1]){
            position = limits[1];
        } else if(position > limits[0]){
            position = limits[0];
        }

        char command[100] = {0};
        snprintf(command, 100, "WL LD %d DG NP GO", (int)position);
        
        this->_connection->write(command);
    }

    virtual void SetLimits(float CWLimit, float CCWLimit){

    }
    virtual void SetVelocity(float velocity){

    }
    virtual void MoveClockwise(void){

    }
    virtual void MoveCounterClockwise(void){

    }
    virtual void Stop(void){

    }

    virtual ~DeiselHD50(){
        this->Stop();
        delete this->_connection;
    }
};

#endif