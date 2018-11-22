
/******************************************************
 * Timer.cpp
******************************************************/
#include "Timer.h"

Timer::Timer()
    : state(0)
    , onInterval(0)
    , offInterval(0)
    , pin(0)
    , enTimeFormat(MILLISECONDS)
{}

void Timer::attach(int pin)
{
    // Attach the Timer to a pin
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
    // Attach the Timer to a pin
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
    // Change the state of the pin
    state ^= 1;
    digitalWrite(pin, state);
}

inline unsigned long Timer::convmintoMilliseconds(int interval)
{
    // Convert the interval time (in minutes/int) and return as milliseconds as unsigned long
    return interval * 60000L;
}

inline unsigned long Timer::convsectoMilliseconds(int interval)
{
    // Convert the interval time (in minutes/int) and return as milliseconds as unsigned long
    return interval * 1000L;
}

void Timer::setIntervals(unsigned long offInterval, unsigned long onInterval)
{
    // Update both the on and off setIntervals
    switch (enTimeFormat)
    {
        case MINUTES:
            this->offInterval = convmintoMilliseconds(offInterval);
            this->onInterval = convmintoMilliseconds(onInterval);
            break;
        case SECONDS:
            this->offInterval = convsectoMilliseconds(offInterval);
            this->onInterval = convsectoMilliseconds(onInterval);
            break;
        default:
            this->offInterval = offInterval;
            this->onInterval = onInterval;
            break;
    }
}

void Timer::setOffInterval(unsigned long offInterval)
{
    // Update/set the off interval time
    switch (enTimeFormat)
    {
        case MINUTES:
            this->offInterval = convmintoMilliseconds(offInterval);
            break;
        case SECONDS:
            this->offInterval = convsectoMilliseconds(offInterval);
            break;
        default:
            this->offInterval = offInterval;
            break;
    }
}

void Timer::setOnInterval(unsigned long onInterval)
{
    // Update/set the on interval time
    switch (enTimeFormat)
    {
        case MINUTES:
            this->onInterval = convmintoMilliseconds(onInterval);
            break;
        case SECONDS:
            this->onInterval = convsectoMilliseconds(onInterval);
            break;
        default:
            this->onInterval = onInterval;
            break;
    }
}

void Timer::setTimeFormat(TimeUnit enTimeFormat)
{
    // Set if we're running in MILLISECONDS or MINUTES
    this->enTimeFormat = enTimeFormat;
}

void Timer::update()
{
    // Update/poll the timers to see if we should toggle the output or not
    unsigned long currentTime;
    currentTime = millis();
    // Toggle the relay if we're at the interval, and our interval time isn't set to zero
    switch (state)
    {
        case 0:
            // Pin low
            if ((currentTime - prevSwitchTime) >= offInterval && offInterval > 0)
            {
                // Toggle the pin if we're at the onInterval time, and our interval time isn't set to zero
                // Save the last time we switched the relay and toggle it
                prevSwitchTime = currentTime;
                changeState();
            }
            break;
        case 1:
            // Pin high
            if ((currentTime - prevSwitchTime) >= onInterval && onInterval > 0)
            {
                // Toggle the pin if we're at the onInterval time, and our interval time isn't set to zero
                // Save the last time we switched the relay and toggle it
                prevSwitchTime = currentTime;
                changeState();
            }
            break;
    }
}