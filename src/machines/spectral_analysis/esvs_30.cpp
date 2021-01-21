#ifndef _ESVS30_APPLICATION
#define _ESVS30_APPLICATION 1

#include "../../../include/machine/spectral_analysis.h"
#include "../../../include/connection/gpib.h"
#include "../../../include/utils/parser.h"
#include <string>
#include <stdio.h>





class ESVS30: public SpectralAnalysis{
private:
    std::string _addr;
    GPIB* _connection;
public:
    
    ESVS30(char* addr){
        this->_addr = addr;
        this->_connection = new GPIB(addr);
        
        this->_connection->setTestResponse(true);
        this->_connection->setTestWrite(true);
        
        this->Initialize();
    }

    /*
    *
    *     Resets the device
    * 
    */
    virtual void Reset(void){

    }

    /*
     *
     *     Set Instrument Mode, Units, Turn on Pre-selector, RBW Band Filter to 6dB, Turn off all active markers, set EMC Option (if available)
     * 
     *     Parameters:
     *         Reset	 Boolean to indicate whether to reset the device
     */
    virtual void Initialize(bool reset=false){
        if(reset){
            this->Reset();
        }
        this->_connection->write("H OFF");
    }

    /*
     *
     *     Queries the Attenuation and Reference level
     *     Attenuation		Value of the attenuation level in dB
     *      
     *     Reference		Value of the reference level in dBuV
     * 
     *     Returns:
     *          vector<float> [Attenuation, Reference]
     *  
     */
    virtual std::vector<float> GetLevel(void){
        char* attenuation = this->_connection->query("ATTENUATION?", "80");
        char* reference = this->_connection->query("LEVEL?", "80");

        std::vector<float> v = { Parser::Float(attenuation), Parser::Float(reference) };
        return v;
    }


    /*
     *      Used to return the current scan/sweep time
     * 
     *      Returns:
     *          SweepTime    SweepTime in seconds
     *  
     */
    virtual float GetSweepTime(void){
        return 0;
    }

    
    /**
     *      Select the detector type for the selected trace
     * 
     *      Parameters:
     *          Detector	0=Peak, 1=QPeak, 2=Average, 3=RMS
     * 
     */
    virtual void ConfigureDetector(int detector){

        switch (detector){
            case 0: this->_connection->write("DETECTOR PEAK"); break;
            case 1: this->_connection->write("DETECTOR QUASIPEAK"); break;
            case 2: this->_connection->write("DETECTOR AVERAGE"); break;
            case 3:  break;
        
        }
    }


    /**
     *      Sets the Bandwidth parameters.
     *      
     *      Parameters:
     *          bandwidth		The resolution bandwidth in Hz
     */
    virtual void ConfigureBandwidth(int bandwidth){
        // Resolution Bandwidth in Hz
        // 10 kHz
        // 120 kHz
        
        if (!(bandwidth == 10000 || bandwidth == 120000)){
            bandwidth = 10000;
        }
        char command[100] = {0};
        snprintf(command, 100, "BANDWIDTH:IF %d", (int) bandwidth);
        this->_connection->write(command);
    }

    /**
     *      Set the reference level and attenuation levels
     * 
     *      Parameters:
     *          attenuation			Value to set the Attenuation to in dB
     * 
     */
    virtual void ConfigureAttenuation(int attenuation){
        char command[100] = {0};
        snprintf(command, 100, "ATTENUATION %d", (int) attenuation);
        this->_connection->write(command);
    }

    /**
     *      Turns the Preamp on or off 
     * 
     *      Parameters:
     *          State			Off = False, On = True
     * 
     */
    virtual void ConfigurePreamp(bool state){
        if(state){
            this->_connection->write("PREAMPLIFIER ON");
        }else{
            this->_connection->write("PREAMPLIFIER OFF");
        }
    }


    /**
     *      Sets the sweep time.
     *      
     *      Parameters:
     *          SweepTime			Time (seconds) of the scan
     *  
     */
    virtual void ConfigureSweepTime(float sweep_time){
        char command[100] = {0};

        if (0 < sweep_time && sweep_time < 1){
            snprintf(command, 100, "SWEEP:TIME %d MS", (int)(sweep_time*1000));
        }
        else{
            snprintf(command, 100, "SWEEP:TIME %d S", (int)(sweep_time));
        }

        this->_connection->write(command);
    }

    /**
     *      Sets the start and stop frequency.
     *      
     *      Parameters:
     *          start			The start frequency in Hz
     *          stop			The stop frequency in Hz
     * 
     */
    virtual void ConfigureFrequencyStartStop(float start, float stop){
        char command1[100] = {0}, command2[100] = {0};

        this->_connection->write("SCAN 1");
        
        snprintf(command1, 100, "SCAN:FREQUENCY:START %d", (int)start);
        this->_connection->write(command1);

        snprintf(command2, 100, "SCAN:FREQUENCY:STOP %d", (int)stop);
        this->_connection->write(command2);

        this->_connection->write("SCAN:SAVE");
    }

    /**
     *      Set the center frequency in Hz
     *  
     */
    virtual void ConfigureFrequencyCenter(float freq){
        char command[100] = {0};
        snprintf(command, 100, "FREQUENCY %.2f", freq);
        
        this->_connection->write(command);
    }


    /**
     *      Starts or stops continuous sweep
     *      
     *      Parameters:
     *          state		Off = 0, On = 1
     * 
     */
    virtual void InitiateContinuous(int state){
        if (state == 0){
            this->_connection->write("SCAN:INTERRUPT");

        }else if(state == 1){
            this->_connection->write("SCAN:CONTINUE");
        }
    }


    /**
     *      Start a new scan with the current settings. The calling software will 
     *      use the AcquisitionStatus function call after this function call completes 
     *      to determine when the scan is complete.
     * 
     */
    virtual void InitiateAcquisition(void){
        this->_connection->write("*CLS;*ESE 1;*SRE 33");
        this->_connection->write("SCAN:BLOCK:RESULTS:CLEAR");
        this->_connection->write("SCAN:RUN;*OPC");
    }


    /**
     *
     *      Query the amplitude values for the active trace
     * 'SCAN:BLOCK 0199,35,37960000,-2.69,32,38000000,-5.69,32,38040000,-4.97,32,38080000,-5.22,32,38120000,-4.60,32,38160000,-3.90,32,38200000,-2.42,32,38240000,-2.54,32,38280000,-6.20,32,38320000,-7.28,32,38360000,-4.32,32,38400000,-3.36,32,38440000,-6.98,32,38480000,-2.74,32,38520000,-4.94,32,38560000,-5.36,32,38600000,-6.34,32,38640000,-4.38,32,38680000,-6.56,32,38720000,-5.42,32,38760000,-2.62,32,38800000,-3.62,32,38840000,-5.20,32,38880000,-4.64,32,38920000,-6.22,32,38960000,-2.74,32,39000000,-5.54,32,39040000,-4.20,32,39080000,-3.70,32,39120000,-3.24,32,39160000,-4.20,32,39200000,-5.54,32,39240000,-5.62,32,39280000,-3.78,32,39320000,-4.00,32,39360000,-6.42,32,39400000,-3.16,32,39440000,-3.00,32,39480000,-7.50,32,39520000,-4.46,32,39560000,-4.30,32,39600000,-4.72,32,39640000,-0.56,0,39680000,-3.24,32,39720000,-4.20,32,39760000,-6.80,32,39800000,-3.62,32,39840000,0.58,0,39880000,-3.64,32,39920000,-3.10,32,39960000,-2.84,32,40000000,-5.42,32,40040000,-5.36,32,40080000,-5.03,32,40120000,-4.29,32,40160000,-1.76,0,40200000,-4.48,32,40240000,-5.24,32,40280000,-7.40,32,40320000,-5.08,32,40360000,-7.58,32,40400000,-7.18,32,40440000,-4.79,32,40480000,-5.11,32,40520000,-3.87,32,40560000,-2.18,32,40600000,-5.83,32,40640000,-7.61,32,40680000,-3.68,32,40720000,-3.20,32,40760000,-4.66,32,40800000,-5.90,32,40840000,-5.02,32,40880000,-4.06,32,40920000,-4.71,32,40960000,-5.55,32,41000000,-3.95,32,41040000,-4.67,32,41080000,-5.77,32,41120000,-4.67,32,41160000,-7.12,32,41200000,-7.00,32,41240000,-4.44,32,41280000,-1.23,0,41320000,-2.97,32,41360000,-5.83,32,41400000,-5.21,32,41440000,-3.33,32,41480000,-4.65,32,41520000,-7.49,32,41560000,-3.60,32,41600000,-4.92,32,41640000,-5.24,32,41680000,-4.16,32,41720000,-6.08,32,41760000,-6.80,32,41800000,-5.07,32,41840000,-2.91,32,41880000,-3.61,32,41920000,-4.17,32,41960000,-0.41,0,42000000,-3.97,32,42040000,-5.96,32,42080000,-3.46,32,42120000,-5.70,32,42160000,-4.88,32,42200000,-3.08,32,42240000,-3.88,32,42280000,-4.70,32,42320000,-3.09,32,42360000,-3.57,32,42400000,-5.37,32,42440000,-4.60,32,42480000,-3.24,32,42520000,-1.42,0,42560000,-5.90,32,42600000,-3.56,32,42640000,-3.94,32,42680000,-4.67,32,42720000,-3.75,32,42760000,-6.33,32,42800000,-3.95,32,42840000,-1.64,0,42880000,-4.33,32,42920000,-6.69,32,42960000,-3.70,32,43000000,-4.24,32,43040000,-6.18,32,43080000,-4.23,32,43120000,-2.91,32,43160000,-3.13,32,43200000,-7.23,32,43240000,-4.15,32,43280000,-6.21,32,43320000,-5.12,32,43360000,-5.70,32,43400000,-5.06,32,43440000,-4.32,32,43480000,-5.78,32,43520000,-5.54,32,43560000,-7.40,32,43600000,-5.07,32,43640000,-3.79,32,43680000,-7.19,32,43720000,-6.07,32,43760000,-5.63,32,43800000,-4.55,32,43840000,-4.12,32,43880000,-4.24,32,43920000,-5.66,32,43960000,-5.74,32,44000000,-3.73,32,44040000,-2.55,32,44080000,-4.23,32,44120000,-6.75,32,44160000,-4.39,32,44200000,-4.81,32,44240000,-4.38,32,44280000,-3.08,32,44320000,-2.92,32,44360000,-4.44,32,44400000,-5.48,32,44440000,-5.86,32,44480000,-2.70,32,44520000,-5.59,32,44560000,-4.57,32,44600000,-3.43,32,44640000,-3.08,32,44680000,-4.22,32,44720000,-3.48,32,44760000,-5.46,32,44800000,-3.02,32,44840000,-1.65,0,44880000,-4.92,32,44920000,-3.37,32,44960000,-7.43,32,45000000,-6.93,32,45040000,-5.23,32,45080000,-5.31,32,45120000,-3.57,32,45160000,-4.47,32,45200000,-4.66,32,45240000,-2.90,32,45280000,-6.28,32,45320000,-5.03,32,45360000,-5.53,32,45400000,-0.47,0,45440000,-7.65,32,45480000,-4.33,32,45520000,-4.01,32,45560000,-5.37,32,45600000,-3.74,32,45640000,-2.64,32,45680000,-3.86,32,45720000,-5.14,32,45760000,-2.09,32,45800000,-4.63,32,45840000,-6.29,32,45880000,-5.09,32\n'
     */
    virtual Dataset<double> GetTraceData(void){
        Dataset<double> dataset((char*)"freq", (char*)"value1", (char*)"value2", NULL);
        return dataset;
    }

    /**
     *      This function is called after InitiateAcquisition to allow the calling 
     *      software to pause until the sweep is complete and new data is available.
     *  
     *      Returns:
     *          int	 0   = Still acquiring data, 
     *               1   = Complete, 
     *              -1   = device cannot determine the status of the acquisition
     * 
     */
    virtual int AcquisitionStatus(void){
        return -1;
    }

    virtual ~ESVS30(){
        delete this->_connection;
    }
};


#endif
