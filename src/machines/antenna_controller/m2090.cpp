
#ifndef _M2090_APPLICATION
#define _M2090_APPLICATION 1

#include "../../../include/machine/antenna_controller.h"
#include "../../../include/log/logApplication.h"
#include "../../../include/connection/gpib.h"
#include "../../../include/utils/parser.h"
#include <string>
#include <stdio.h>


class M2090: public AntennaController{
private:
    std::string _addr;
    GPIB* _connection;
public:
    M2090(char* addr){
        this->_addr = addr;
        this->_connection = new GPIB(addr);
        
        this->_connection->setTestResponse(true);
        this->_connection->setTestWrite(true);

        this->Initialize();
    }

     /*
    *     Resets the device
    * 
    */
    virtual void Reset(void){
        this->_connection->write("*RST");
    }

    /*
     *     Initialize 
     *     
     *     Parameters: 
     *         reset		Boolean to indicate whether to reset the device
     */
    virtual void Initialize(bool reset=false){
        if(reset){
            this->Reset();
        }
        this->_connection->write("N2;TWR NRM;TWR TWO");
    }

    /*
     *
     *     Initialize
     *     
     *     Parameters:
     *         reset		Boolean to indicate whether to reset the device
     */
    virtual bool CheckStatus(float targerValue){
        char* buffer = this->_connection->query("CP?", std::to_string(targerValue).c_str());
        float value = Parser::Float(buffer);

        if ((int)value == (int)targerValue){
            return true;
        }
        return false;
    }

    /*
    *
    *       Returns the current antenna polarization
    * 
    *       Returns:
    *           Integer 0 = vertical, 1 = horizontal 
    */
    virtual int GetPolarization(void){
        char* possition = this->_connection->query("P?", "0");
        return Parser::Interger(possition);
    }

    /**
     * 
     * 
     *      Returns the upper and lower limits through pointers
     * 
     *      UpperLimit			The highest position the antenna can be set
     *      LowerLimit			The lowest position the antenna can be set
     * 
     *      Returns:
     *          vector<float> [UpperLimit, LowerLimit]
     * 
     */
    virtual std::vector<float> GetLimits(void){
        char* upper_limit = this->_connection->query("UL?", "100");
        char* lower_limit = this->_connection->query("LL?", "0");
        
        std::vector<float> v = {Parser::Float(upper_limit), Parser::Float(lower_limit)};
        return v;
    }
    

    /*
     *
     *      Returns the current antenna position
     *      
     *      Returns:
     *          Float   The height of the antenna
     * 
     */    
    virtual float GetPosition(void){
        char* value = this->_connection->query("CP?", "0");
        return Parser::Float(value);
    }


    /*
     *      Sets the antenna position
     *      
     *      Parameters:
     *          position        The height to set the antenna
     * 
     */
    virtual void SetPosition(float position){
        std::vector<float> limits = this->GetLimits();

        if (position < limits[1]){
            position = limits[1];
        }
        else if(position > limits[0]){
            position = limits[0];
        }

        char command[100] = {0};
        snprintf(command, 100, "TG %d;SK", (int)position);

        this->_connection->write(command);
    }

    /*
     *      Move tower boom up
     */
    virtual void MoveUp(void){
        this->_connection->write("UP");
    }

    /*
     *      Move tower boom down
     */
    virtual void MoveDown(void){
        this->_connection->write("DN");
    }


    /*
     *      Stops the currently moving antenna
     */
    virtual void Stop(void){
        this->_connection->write("ST");
    }

    /*
     *      Sets the upper and lower limits of the antenna height
     *      
     *      Parameters:
     *          upperLimit      The highest position the antenna can be set
     *          lowerLimit      The lowest position the antenna can be set
     */
    virtual void SetLimits(float upperLimit, float lowerLimit){
        int polarization = this->GetPolarization();
        char command[100] = {0};

        if (polarization == 1){ // horizontal
            snprintf(command, 100, "UH %d;LH %d", (int)upperLimit, (int)lowerLimit);
            this->_connection->write(command);
        } 
        else if(polarization == 0){ //vertical
            snprintf(command, 100, "UV %d;LV %d", (int)upperLimit, (int)lowerLimit);
            this->_connection->write(command);
        }
        else{
            LogApplication::error("Não foi possível identificar a polarização");
        }
            
    }

    /**
     *      Sets the antenna polarization
     *         
     *      Parameters:
     *          Polarization    0 = vertical, 1 = horizontal
     */    
    virtual void SetPolarization(int polarization){
        if (polarization == 1){ //horizontal
            this->_connection->write("PH");

        }else if(polarization == 0){ //vertical
            this->_connection->write("PV");
        }
    }

    
    virtual ~M2090(){
        this->Stop();
        delete this->_connection;
    }
};

#endif
