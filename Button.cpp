#include "Arduino.h"
#include "Button.h"

void Button::setPin(int pin) {
  this->pin = pin;
}
void Button::init(){
  pinMode(this->pin, INPUT);
}
void Button::nowPressed() {
  this->pressed = true;
}
void Button::nowReleased() {
  this->pressed = false;
}
int Button::getPin() {
  return(this->pin);
}
long Button::getTimestamp(){
  return(timestamp);
}
bool Button::isItPressed() {
  if(millis() >= this->timestamp && !tempPress){
    this->tempPress = digitalRead(this->pin);
    this->pressed = false;
  }
  if(tempPress && !digitalRead(this->pin)){
    this->timestamp = millis();
    this->pressed = true;
    this->tempPress = false;
  }
  return(this->pressed);
}
