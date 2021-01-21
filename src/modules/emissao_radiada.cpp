#include "../../include/service.h"
#include "../../include/utils/time.h"
#include "../machines/antenna_controller/m2090.cpp"
#include "../machines/spectral_analysis/esvs_30.cpp"
#include "../machines/turntable/deisel_hd50.cpp"
#include "../../include/utils/math.h"
#include "../../include/log/logApplication.h"



// [11:50 AM, 10/5/2020] Bruno: Fazer um programa em Phyton que faça o seguinte:
// [11:50 AM, 10/5/2020] Bruno: Faça uma varredura na esvs30 na frequência de 30 MHz até 1GHz
// [11:51 AM, 10/5/2020] Bruno: Gire a turn table em um determinado passo, usamos hoje 45°
// [11:51 AM, 10/5/2020] Bruno: Repita o scan
// [11:52 AM, 10/5/2020] Bruno: Depois troque a polarização da antena e repita os passos
// [11:52 AM, 10/5/2020] Bruno: Depois com os 8 arquivos de pontos faça um arquivo novo só com os máximos de cada ponto
// [11:53 AM, 10/5/2020] Bruno: E se possível mostre esse último arquivo na tela


class EmissaoRadiada: public Service{
private:
    float _start_freq;
    float _stop_freq;
    int _step_angle;

    SpectralAnalysis* _spectral_analysis= nullptr;
    AntennaController* _antenna = nullptr;
    Turntable* _turntable = nullptr;    


public:
    EmissaoRadiada(float start_freq, float stop_freq, int step_angle){
        this->setStartFrequency(start_freq);
        this->setStopFrequency(stop_freq);
        this->setStepAngleFrequency(step_angle);

        this->OpenSession();
        
    }

    void setStartFrequency(float value){
        this->_start_freq = value;
    }
    void setStopFrequency(float value){
        this->_stop_freq = value;
    }
    void setStepAngleFrequency(int value){
        if(value < 1){ value = 1; }
        if(value > 360){ value = 360; }
        this->_step_angle = value;
    }

    float getStartFrequency(){
        return this->_start_freq;
    }
    float getStopFrequency(){
        return this->_stop_freq;
    }
    int getStepAngleFrequency(){
        return this->_step_angle;
    }
    


    virtual int main(void){
        LogApplication log = LogApplication::stream(); 
        this->_spectral_analysis->ConfigureFrequencyStartStop(this->_start_freq, this->_stop_freq);
        this->_spectral_analysis->ConfigureSweepTime(0.002);
        this->_spectral_analysis->ConfigureBandwidth(120000);
        this->updateProgress(1);
        this->msleep(500);

        std::vector<int> turtable_limits = this->_turntable->GetLimits();
        std::vector<int> angles = Math::range<int, int> (turtable_limits[1], turtable_limits[0], this->_step_angle);
        // polarization    0 = vertical, 1 = horizontal
        for (int polarization = 0; polarization < 2; polarization++){
            this->_antenna->SetPolarization(polarization);
            
            // while (this->_antenna->GetPolarization() != polarization){ // testar esse passo
            //     Time::sleep_time(1);
            //     LogApplication::info("Esperando Polarização da antena");
            // }
            
            for(auto angle: angles){
                this->_turntable->SetPosition(angle);

                // while(this->_turntable->CheckStatus(angle)){
                //     Time::sleep_time(1);
                //     LogApplication::info("Esperando turntable");
                // }

                this->_spectral_analysis->InitiateAcquisition();

                while (this->_spectral_analysis->AcquisitionStatus() == 0){
                    Time::sleep_time(1);
                    LogApplication::info("Esperando dados");
                }
                
                auto dataset = this->_spectral_analysis->GetTraceData();
                log << dataset.exportCSV();
                log.print("DATASET");
                
            }
        }
        this->updateProgress(50);
        Time::sleep_time(1);
        this->updateProgress(100);
        
        return 0;
    }

    void OpenSession(void){
        this->_spectral_analysis = new ESVS30((char*)"GPIB0::27::INSTR");
        this->_antenna = new M2090((char*) "GPIB0::17::INSTR");
        this->_turntable = new DeiselHD50((char*) "GPIB0::7::INSTR");
    }

    void CloseSession(void){
        if(this->_spectral_analysis){
            delete this->_spectral_analysis;
        }
        if(this->_antenna){
            delete this->_antenna;
        }
        if(this->_turntable){
            delete this->_turntable;
        }
    }

    virtual ~EmissaoRadiada(){
        this->CloseSession();
    }
};

