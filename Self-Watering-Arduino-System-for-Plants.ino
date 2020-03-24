#include "Arduino.h"
#include "Plant.h"
#include "Display.h"

// include the library code:
#include <LiquidCrystal.h>



// Class for buttons
class Button {
  private:
    int pin; // its pin
    bool pressed; // if button is pressed
    
  public:
    Button(int pin) {
      // 'this->' used to make the difference between the attributes of 
      // the class and the local variables created from the parameter.
      this->pin = pin;
      this->pressed = false;
      pinMode(this->pin, INPUT);
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
    bool isItPressed() {
      this->pressed = digitalRead(this->pin);
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

//plantNam, minMoist, maxMoist, prefDirLight
Plant* plants[]= {
  new Plant("Mint", 20, 40, 2*60)
  , new Plant("Ginger", 20, 40, 2*60)
  , new Plant("Sunflower", 20, 40, 4*60)
  , new Plant("Cactus", 0, 20, 5*60)
  , new Plant("Rosemary", 20, 40, 2*60)
};


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 11, en = 12, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// make a display object
Display *LCD = new Display();


void setup() {
  Serial.begin(9600);
  Serial.println("I can print");
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  // first and second plant on display
  updateDisplay();
  Serial.println("Hello World!");

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // this below fucks it up and stops the Arduino code. But I get no error message when compiling. The list should be changed. It certainly doesn't work as it is! //
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  for(int i = 0; i < sizeof(plants)/2; i++){ // whole size divided by size of a char
    LCD->addPlant(*plants[i]);
  }
  
  lcd.display();
}

void loop() {
  // madeshift listeners
  if(buttonDown->isItPressed()){
    LCD->scrollDown();
    Serial.println("buttonDown pressed");
  }
  if(buttonEnter->isItPressed()){
    lcd.noDisplay();
    Serial.println("buttonEnter pressed");
  }
  if(buttonUp->isItPressed()){
    LCD->scrollUp();
    Serial.println("buttonUp pressed");
  }

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
  lcd.print(LCD->getTopTxt());
  lcd.setCursor(0, 1);
  lcd.print(LCD->getBotTxt());
  Serial.println(LCD->getTopTxt() + "\n" + LCD->getBotTxt());
}
