// Timer_basic Example written using an Arduino Uno
#include <Timer.h>

// Create the timer object
Timer builtinLED = Timer();

void setup()
{
    // put your setup code here, to run once:
	// Attach the timer object to the built-in LED
	builtinLED.attach(LED_BUILTIN, SECONDS);
	// Set how long the pin will be off for
	builtinLED.setOffInterval(1);
	// Set how long the pin will be on for
	builtinLED.setOnInterval(5);
}

void loop()
{

	// put your main code here, to run repeatedly:
	// Poll the timer
	builtinLED.update();
}
