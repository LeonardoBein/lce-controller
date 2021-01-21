#include <vector>
#include "../utils/dataset.h"

class SpectralAnalysis{

public:

    /*
    *
    *     Resets the device
    * 
    */
    virtual void Reset(void) = 0;

    /*
     *
     *     Set Instrument Mode, Units, Turn on Pre-selector, RBW Band Filter to 6dB, Turn off all active markers, set EMC Option (if available)
     * 
     *     Parameters:
     *         Reset	 Boolean to indicate whether to reset the device
     */
    virtual void Initialize(bool reset) = 0;

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
    virtual std::vector<float> GetLevel(void) = 0;


    /*
     *      Used to return the current scan/sweep time
     * 
     *      Returns:
     *          SweepTime    SweepTime in seconds
     *  
     */
    virtual float GetSweepTime(void) = 0; 

    
    /**
     *      Select the detector type for the selected trace
     * 
     *      Parameters:
     *          Detector	0=Peak, 1=QPeak, 2=Average, 3=RMS
     * 
     */
    virtual void ConfigureDetector(int detector) = 0;


    /**
     *      Sets the Bandwidth parameters.
     *      
     *      Parameters:
     *          bandwidth		The resolution bandwidth in Hz
     */
    virtual void ConfigureBandwidth(int bandwidth) = 0;

    /**
     *      Set the reference level and attenuation levels
     * 
     *      Parameters:
     *          attenuation			Value to set the Attenuation to in dB
     * 
     */
    virtual void ConfigureAttenuation(int attenuation) = 0;

    /**
     *      Turns the Preamp on or off 
     * 
     *      Parameters:
     *          State			Off = False, On = True
     * 
     */
    virtual void ConfigurePreamp(bool state) = 0;


    /**
     *      Sets the sweep time.
     *      
     *      Parameters:
     *          SweepTime			Time (seconds) of the scan
     *  
     */
    virtual void ConfigureSweepTime(float sweep_time) = 0;

    /**
     *      Sets the start and stop frequency.
     *      
     *      Parameters:
     *          start			The start frequency in Hz
     *          stop			The stop frequency in Hz
     * 
     */
    virtual void ConfigureFrequencyStartStop(float start, float stop) = 0;

    /**
     *      Set the center frequency in Hz
     *  
     */
    virtual void ConfigureFrequencyCenter(float freq) = 0;


    /**
     *      Starts or stops continuous sweep
     *      
     *      Parameters:
     *          state		Off = 0, On = 1
     * 
     */
    virtual void InitiateContinuous(int state) = 0;


    /**
     *      Start a new scan with the current settings. The calling software will 
     *      use the AcquisitionStatus function call after this function call completes 
     *      to determine when the scan is complete.
     * 
     */
    virtual void InitiateAcquisition(void) = 0;


    /**
     *
     *      Query the amplitude values for the active trace
     * 
     */
    virtual Dataset<double> GetTraceData(void) = 0;

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
    virtual int AcquisitionStatus(void) = 0;

    virtual ~SpectralAnalysis(){}

};

