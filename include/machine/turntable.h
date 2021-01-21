
#include <vector>

class Turntable {
public:    
    /*
    *   Resets the device
    * 
    */
    virtual void Reset(void) = 0;
    
    /*
    *   Checks if the current movement is complete
    * 
    *   Parameters:
    *      targetValue	The target position.  When reached, motion can stop.
    * 
    */
    virtual bool CheckStatus(float targetValue) = 0;
    
    /*
    *   Returns the upper and lower limits through pointers 
    * 
    *   CWLimit         The highest angle the turntable can be set
    *   CCWLimit        The lowest angle the turntable can be set
    * 
    *   Returns:
    *       std::vector<int> [CWLimit, CCWLimit]
    * 
    */
    virtual std::vector<int> GetLimits(void) = 0;
    
    /*
    *   Returns the current turntable position
    *   
    *   Returns:
    *       Float current position
    */
    virtual float GetPosition(void) = 0;

    /*
    *   Sets the turntable position 
    *   
    *   Parameters:
    *       Position	The position of the turntable in degrees
    */
    virtual void SetPosition(float position) = 0;

    /*
    *   Sets the upper and lower limits of the turntable
    * 
    *   Parameters:
    *       CWLimit		The largest angle the turntable can be set when turning clockwise
    *       CCWLimit	The smallest angle the turntable can be set when turning counterclockwise
    */
    virtual void SetLimits(float CWLimit, float CCWLimit) = 0;
    
    /*
    *   Sets the turntable Velocity
    *   
    *   Parameters:
    *       Velocity	The velocity of the turntable
    */
    virtual void SetVelocity(float velocity) = 0;

    /*
    *   Sets the turntable in motion (clockwise direction)
    */
    virtual void MoveClockwise(void) = 0;
    
    /*
    *   Sets the turntable in motion (counter clockwise direction)
    */
    virtual void MoveCounterClockwise(void) = 0;

    /*
    *   Stops the current movement
    */
    virtual void Stop(void) = 0;

    virtual ~Turntable(){}


};


