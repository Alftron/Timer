
/******************************************************
 * Timer.cpp
******************************************************/
#include "Timer.h"

Timer::Timer()
    /**
     * Constructor - provides default values of state(0), offTime(0), pin(0), enTimeFormat(MILLISECONDS)
    */
    : state(0)
    , onTime(0)
    , offTime(0)
    , pin(0)
    , enTimeFormat(MILLISECONDS)
{}

void Timer::attach(int pin)
{
    /**
     * Attach the timer to a pin without specifying unit of time (default milliseconds)
    */
    this->pin = pin;
    state = 0;
    #if defined(ARDUINO_STM_NUCLEO_F103RB) || defined(ARDUINO_GENERIC_STM32F103C)
        pinMode(pin, (WiringPinMode)OUTPUT); 
    #else
        pinMode(pin, OUTPUT);
    #endif
}

void Timer::attach(int pin, TimeUnit enTimeFormat)
{
    /**
     * Attach the timer to a pin and specify the unit of time (MILLISECONDS, SECONDS, MINUTES)
    */
    this->pin = pin;
    state = 0;
    #if defined(ARDUINO_STM_NUCLEO_F103RB) || defined(ARDUINO_GENERIC_STM32F103C)
        pinMode(pin, (WiringPinMode)OUTPUT); 
    #else
        pinMode(pin, OUTPUT);
    #endif
    this->enTimeFormat = enTimeFormat;
}

inline void Timer::changeState()
{
    /**
     * Private function: Change the state of the pin
    */
    state ^= 1;
    digitalWrite(pin, state);
}

inline unsigned long Timer::convmintoMilliseconds(int timeToConvert)
{
    /**
     * Private function: Convert the time given (in minutes/int) and return as milliseconds as unsigned long
    */
    return timeToConvert * 60000L;
}

inline unsigned long Timer::convsectoMilliseconds(int timeToConvert)
{
    /**
     * Private function: Convert the time given (in minutes/int) and return as milliseconds as unsigned long
    */
    return timeToConvert * 1000L;
}

void Timer::setOffTime(unsigned long offTime)
{
    /**
     * Set the off time
    */
    switch (enTimeFormat)
    {
        case MINUTES:
            this->offTime = convmintoMilliseconds(offTime);
            break;
        case SECONDS:
            this->offTime = convsectoMilliseconds(offTime);
            break;
        default:
            this->offTime = offTime;
            break;
    }
}

void Timer::setOnTime(unsigned long onTime)
{
    /**
     * Set the on time
    */
    switch (enTimeFormat)
    {
        case MINUTES:
            this->onTime = convmintoMilliseconds(onTime);
            break;
        case SECONDS:
            this->onTime = convsectoMilliseconds(onTime);
            break;
        default:
            this->onTime = onTime;
            break;
    }
}

void Timer::setTimeFormat(TimeUnit enTimeFormat)
{
    /**
     * Set if the timer is running in MILLISECONDS, SECONDS or MINUTES, and convert any existing times.
    */
    this->enTimeFormat = enTimeFormat;

    // Need to convert any existing times just in case they have already been set
    switch (enTimeFormat)
    {        
        case MINUTES:
            this->offTime = convmintoMilliseconds(this->offTime);
            this->onTime = convmintoMilliseconds(this->onTime);
            break;
        case SECONDS:
            this->offTime = convsectoMilliseconds(this->offTime);
            this->onTime = convsectoMilliseconds(this->onTime);
            break;
        default:
            this->onTime = onTime;
            break;

    }
}

void Timer::setTimer(unsigned long offTime, unsigned long onTime)
{
    /**
     * Set both the off and on times
    */
    switch (enTimeFormat)
    {
        case MINUTES:
            this->offTime = convmintoMilliseconds(offTime);
            this->onTime = convmintoMilliseconds(onTime);
            break;
        case SECONDS:
            this->offTime = convsectoMilliseconds(offTime);
            this->onTime = convsectoMilliseconds(onTime);
            break;
        default:
            this->offTime = offTime;
            this->onTime = onTime;
            break;
    }
}

void Timer::update()
{
    /**
     * Update/poll the timer(s) to see if we should toggle the pin or not
    */
    unsigned long currentTime;
    currentTime = millis();
    // Toggle the relay if we're at the specified time, and the time isn't set to zero
    switch (state)
    {
        case 0:
            // Pin low
            if ((currentTime - prevSwitchTime) >= offTime && offTime > 0)
            {
                // Toggle the pin if we're at the offTime, and the offTime isn't set to zero
                // Save the last time we switched the relay and toggle it
                prevSwitchTime = currentTime;
                changeState();
            }
            break;
        case 1:
            // Pin high
            if ((currentTime - prevSwitchTime) >= onTime && onTime > 0)
            {
                // Toggle the pin if we're at the onTime, and the onTime isn't set to zero
                // Save the last time we switched the relay and toggle it
                prevSwitchTime = currentTime;
                changeState();
            }
            break;
    }
}