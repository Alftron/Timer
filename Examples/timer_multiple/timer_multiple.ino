// Timer_basic Example written using an Arduino Uno
#include <Timer.h>

byte LED1 = 17;

// Create timer objects
Timer builtinLED = Timer();
Timer externalLED = Timer();

void setup()
{
    // Attach the timer object to the built-in LED
    builtinLED.attach(LED_BUILTIN, SECONDS);
    // Set how long the pin will be off for
    builtinLED.setOffTime(1);
    // Set how long the pin will be on for
    builtinLED.setOnTime(5);

    // Attach the timer object to the built-in LED
    externalLED.attach(LED1, MINUTES);
    // Set both off and on intervals in the arguments
    externalLED.setTimer(1, 5);
}

void loop()
{
    // Poll both timers
    builtinLED.update();
    LED1.update();
}
