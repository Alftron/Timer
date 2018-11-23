# Timer

(Another) Timer library for Arduino. Mainly wrote for myself to improve my Github skills, and to make my first Arduino library but feel free to use it (and adapt it) if you want to!

## GitHub Page

The GitHub project page can be found [here](https://github.com/Alftron/Timer)

## Installation and download

Install through your IDE Library Manager or download the latest version [here](https://github.com/Alftron/Timer/archive/master.zip) and put the "Timer" folder in your Arduino "libraries" folder.

## Documentation

Documentation can be found in the "docs" folder or generated using Doxygen with the Doxyfile config

## Basic usage

```cpp
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
```
