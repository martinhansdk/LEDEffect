/*
  LEDEffect.cpp - Library for LED Effecs.
  Created by Harrison H. Jones, October 3, 2014.
*/

#if defined (SPARK)
#include "application.h"
#else
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#endif

#include "LEDEffect.h"

LEDEffect::LEDEffect(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
  _time = millis();
  _brightness = 125;
  _fadeAmount = 5;    // how many points to fade the LED by
  _fadeDirection = _fadeAmount; 
  _ledState = OFF;
  _ledDelay = 30; // in ms
}

void LEDEffect::update()
{
  if((millis() - _time) > _ledDelay)
    {
      _time = millis();
      switch(_ledState) {
      case OFF:
	_brightness = 0;
	break;
      case ON:
	_brightness = 255;
	break;
      case BREATH:
	// change the _brightness for next time through the loop:
	_brightness = _brightness + _fadeDirection;
	// reverse the direction of the fading at the ends of the fade:
	if (_brightness == 0)
	  _fadeDirection = _fadeAmount;
	else if (_brightness == 255)
	  _fadeDirection = -_fadeAmount;
	break;
      case FADE_DOWN:
	// change the _brightness for next time through the loop:
	_brightness = _brightness - _fadeAmount;
	// reverse the direction of the fading at the ends of the fade:
	if (_brightness == 0)
	  _brightness = 255;
	break;
      case FADE_UP:
	// change the _brightness for next time through the loop:
	_brightness = _brightness + _fadeAmount;
	// reverse the direction of the fading at the ends of the fade:
	if (_brightness == 255)
	  _brightness = 0;
	break;
      case BLINK:
	if(_brightness == 255)
	  _brightness = 0;
	else
	  _brightness = 255;
	break;
      case DIM:
	break;
      }
    }
  analogWrite(_pin, _brightness);  
}
void LEDEffect::off()
{
  _ledState = OFF;
  _ledDelay = 10;
}

void LEDEffect::on()
{
  _ledState = ON;
  _ledDelay = 10;
}

void LEDEffect::breath(int ledDelay)
{
  if(_brightness == 0)
    _fadeDirection = _fadeAmount;
  else if(_brightness == 255)
    _fadeDirection = -_fadeAmount;
  _ledState = BREATH;
  _ledDelay = ledDelay;
}

void LEDEffect::fadeDown(int ledDelay)
{
  if(_brightness == 0)
    _brightness = 255;
  _fadeDirection = -_fadeAmount;
  _ledState = FADE_DOWN;
  _ledDelay = ledDelay;
}

void LEDEffect::fadeUp(int ledDelay)
{
  if(_brightness == 255)
    _brightness = 0;
  _fadeDirection = _fadeAmount;
  _ledState = FADE_UP;
  _ledDelay = ledDelay;
}

void LEDEffect::blink(int ledDelay)
{
  _ledState = BLINK;
  _ledDelay = ledDelay;
}

void LEDEffect::dim(unsigned char brightness)
{
  _ledState = DIM;
  _brightness = brightness;
  _ledDelay = 1000;   // Not really required. 
}
