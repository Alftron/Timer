
/******************************************************
 * Timer.h
******************************************************/ 

#ifndef Timer_h
#define Timer_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/**
   * Enumerator for the unit of time (MILLISECONDS, SECONDS or MINUTES)
*/
enum TimeUnit
{
   /**
      * Specify time in milliseconds
   */
   MILLISECONDS = 0,
   /**
      * Specify time in seconds
   */
   SECONDS,
   /**
      * Specify time in minutes
   */
   MINUTES
};

class Timer
{
   public:
      Timer();
      void attach(int pin);
      void attach(int pin, TimeUnit enTimeFormat);
      void setTimer(unsigned long offTime, unsigned long onTime);
      void setOnTime(unsigned long onTime);
      void setOffTime(unsigned long offTime);
      void setTimeFormat(TimeUnit enTimeFormat);
      void update();

   protected:
      /**
         * Holds the Arduino pin number that will be used with the timer
      */
      uint8_t pin;
      /**
         * Holds the state of the Arduino pin (0 for LOW, 1 for HIGH)
      */
      uint8_t state;
      /**
         * Holds the time the pin will be on for
      */
      unsigned long onTime;
      /**
         * Holds the time the pin will be off for
      */
      unsigned long offTime;
      /**
         * Enumerator for the unit of time (MILLISECONDS, SECONDS or MINUTES)
      */
      TimeUnit enTimeFormat;

   private:
      unsigned long prevSwitchTime;
      inline void changeState();
      inline unsigned long convtoMilliseconds(int timeToConvert);
    
};

#endif
