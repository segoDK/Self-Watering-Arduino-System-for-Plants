// include the libraries
#include "Arduino.h"
#include "Plant.h"
#include "Display.h"
#include <LiquidCrystal.h>



// Class for buttons
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
    void setPin(int pin) {
      this->pin = pin;
    }
    void nowPressed() {
      this->pressed = true;
    }
    void nowReleased() {
      this->pressed = false;
    }
    int getPin() {
      return(this->pin);
    }
    long getTimestamp(){
      return(timestamp);
    }
    bool isItPressed() {
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
    
};


//////////////////////////
//  Internal variables  //
//////////////////////////
// buttons to interact with the menu, objects defined with a pin
Button *buttonUp = new Button(7);
Button *buttonEnter = new Button(8);
Button *buttonDown = new Button(9);

// make plant objects (constructor defined in Plant.h)
// - Plant(plantName, minMoist, maxMoist, prefDirLight) - 
// - plant name, minimum- and maximum moist percentage, preffered time of direct daylight [minutes] - 
Plant* plants[]= {
  new Plant("Mint", 20, 40, 2*60)
  , new Plant("Ginger", 20, 40, 2*60)
  , new Plant("Sunflower", 20, 40, 4*60)
  , new Plant("Cactus", 0, 20, 5*60)
  , new Plant("Rosemary", 20, 40, 2*60)
};

int pASize = sizeof(plants)/2; // whole size divided by size of a char


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 11, en = 12, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// make a display object (constructor defined in Display.h)
Display *LCD = new Display();


void setup() {
  Serial.begin(9600);
  Serial.println("\n");
  Serial.println(timestamp() + "Hello World!");
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  // first and second plant on display
  LCD->updatePlants(*plants, 0, 1, pASize);
  updateDisplay();
  

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // this below fucks it up and stops the Arduino code. But I get no error message when compiling. The list should be changed. It certainly doesn't work as it is! //
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /*
  for(int i = 0; i < sizeof(plants)/2; i++){ // whole size divided by size of a char
    LCD->addPlant(*plants[i]);
  }
  */
  
  lcd.display();
  Serial.println(timestamp() + "LCD have been printed/displayed");
}

void loop() {
  // madeshift listeners
  //if(millis() > buttonDown->getTimestamp() + 500/*milli sec delay*/){
    bool tempDown = buttonDown->isItPressed();
    if(tempDown){
      LCD->scrollDown(*plants, pASize);
      Serial.print(timestamp() + "Down pressed = ");
      Serial.println(String(tempDown));
    }
  //}
  //if(millis() > buttonEnter->getTimestamp() + 500){
    bool tempEnter = buttonEnter->isItPressed();
    if(tempEnter){
      lcd.noDisplay();
      Serial.print(timestamp() + "Enter pressed = ");
      Serial.println(String(tempEnter));
    }
  //}
  //if(millis() > buttonUp->getTimestamp() + 500){
    bool tempUp = buttonUp->isItPressed();
    if(tempUp){
      LCD->scrollUp(*plants, pASize);
      Serial.print(timestamp() + "Up pressed = ");
      Serial.println(String(tempUp));
    }
  //}
  
  /*
  // Turn off the display:
  lcd.noDisplay();
  delay(500);
  // Turn on the display:
  lcd.display();
  delay(500);
  */
  
}


void updateDisplay(){
  lcd.setCursor(0, 0);
  lcd.print(LCD->getTopTxt()); Serial.println(timestamp() + "top text: " + LCD->getTopTxt());
  lcd.setCursor(0, 1); 
  lcd.print(LCD->getBotTxt()); Serial.println(timestamp() + "bot text: " + LCD->getBotTxt());
}



// doesn't work - but should make a propper timestamp for the Serial.print()
String timestamp(){
  long tempMilli = millis();
  long tempSec = tempMilli/1000;
  long tempMin = tempSec/60;
  long tempHour = tempMin/60;

  tempMin =- -tempHour*60;
  tempSec =- -tempMin*60;
  tempMilli =- -tempMin*100;
  
  return(String(tempHour) + ":"
       + String(tempMin) + ":"
       + String(tempSec) + ":"
       + String(tempMilli) + " - ");
       
}
