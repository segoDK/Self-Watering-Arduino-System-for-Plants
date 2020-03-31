#ifndef Button_h
#define Button_h

#include "Arduino.h"

  class Button {
    private:
      int pin; // its pin
      bool pressed; // if button is pressed
      bool tempPress; // if button is pressed this moment
      long timestamp; // time of buttonpress

    public:
      Button(int pin) {
        // 'this->' used to make the difference between the attributes of
        // the class and the local variables created from the parameter.
        this->pin = pin;
        this->pressed = false;
        pinMode(this->pin, INPUT);
        this->timestamp = millis();
      }
      
      void setPin(int pin);
      
      void nowPressed();
      void nowReleased();
      
      int getPin();
      long getTimestamp();
      
      bool isItPressed();

  }; // don't forget the semicolon at the end of the class

#endif
