
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

enum TimeUnit
{
   MILLISECONDS = 0,
   SECONDS,
   MINUTES
};

class Timer
{
   public:
      Timer();
      void attach(int pin);
      void attach(int pin, TimeUnit enTimeFormat);
      void setIntervals(unsigned long offInterval, unsigned long onInterval);
      void setOnInterval(unsigned long onInterval);
      void setOffInterval(unsigned long offInterval);
      void setTimeFormat(TimeUnit enTimeFormat);
      void update();

   protected:
      uint8_t pin;
      uint8_t state;
      unsigned long onInterval;
      unsigned long offInterval;
      unsigned long prevSwitchTime;
      TimeUnit enTimeFormat;

   private:
      inline void changeState();
      inline unsigned long convmintoMilliseconds(int interval);
      inline unsigned long convsectoMilliseconds(int interval);
    
};

#endif
