#include <vector>

class AntennaController{
public:

    /*
    *     Resets the device
    * 
    */
    virtual void Reset(void) = 0;

    /*
     *     Initialize 
     *     
     *     Parameters: 
     *         reset		Boolean to indicate whether to reset the device
     */
    virtual void Initialize(bool reset) = 0;

    /*
     *
     *     Initialize
     *     
     *     Parameters:
     *         reset		Boolean to indicate whether to reset the device
     */
    virtual bool CheckStatus(float targerValue) = 0;

    /*
    *
    *       Returns the current antenna polarization
    * 
    *       Returns:
    *           Integer 0 = vertical, 1 = horizontal 
    */
    virtual int GetPolarization(void) = 0;

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
    virtual std::vector<float> GetLimits(void) = 0;
    

    /*
     *
     *      Returns the current antenna position
     *      
     *      Returns:
     *          Float   The height of the antenna
     * 
     */    
    virtual float GetPosition(void) = 0;


    /*
     *      Sets the antenna position
     *      
     *      Parameters:
     *          position        The height to set the antenna
     * 
     */
    virtual void SetPosition(float position) = 0;

    /*
     *      Move tower boom up
     */
    virtual void MoveUp(void) = 0;

    /*
     *      Move tower boom down
     */
    virtual void MoveDown(void) = 0;


    /*
     *      Stops the currently moving antenna
     */
    virtual void Stop(void) = 0;

    /*
     *      Sets the upper and lower limits of the antenna height
     *      
     *      Parameters:
     *          upperLimit      The highest position the antenna can be set
     *          lowerLimit      The lowest position the antenna can be set
     */
    virtual void SetLimits(float upperLimit, float lowerLimit) = 0;

    /**
     *      Sets the antenna polarization
     *         
     *      Parameters:
     *          Polarization    0 = vertical, 1 = horizontal
     */    
    virtual void SetPolarization(int polarization) = 0;

    virtual ~AntennaController(){}

};

