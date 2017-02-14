/*
	LEDEffect.h - Library for LED Effecs.
	Created by Harrison H. Jones, October 3, 2014.
*/

#ifndef LEDEffect_h
#define LEDEffect_h

#if defined (SPARK)
#include "application.h"
#else
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#endif

class LEDEffect
{
  public:
	LEDEffect(int pin);
	void update();
	void off();
	void on();
	void breath(int ledDelay);
	void fadeDown(int ledDelay);
	void fadeUp(int ledDelay);
	void blink(int ledDelay);
	void dim(unsigned char brightness);
  private:
        enum State_t : unsigned char { OFF, ON, BREATH, FADE_DOWN, FADE_UP, BLINK, DIM };

	int _pin;
	unsigned char _brightness;
	unsigned char _fadeAmount;    // how many points to fade the LED by
	unsigned char _fadeDirection; 
	State_t _ledState;     // 
	int _ledDelay; // in ms
	unsigned long _time;
};

#endif
