// Timer_basic Example written using an Arduino Uno
#include <Timer.h>

// Create the timer object
Timer builtinLED = Timer();

void setup()
{
	// Attach the timer object to the built-in LED
	builtinLED.attach(LED_BUILTIN, SECONDS);
	// Set how long the pin will be off for
	builtinLED.setOffTime(1);
	// Set how long the pin will be on for
	builtinLED.setOnTime(5);
}

void loop()
{
	// Poll the timer
	builtinLED.update();
}
