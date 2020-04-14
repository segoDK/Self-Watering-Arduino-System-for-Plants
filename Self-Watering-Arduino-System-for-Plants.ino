// include the libraries
#include "Arduino.h"
#include "Plant.h"
#include "Display.h"
#include "Button.h"
#include <LiquidCrystal.h>

////////////////////////
//  Internal Objects  //
////////////////////////
// buttons to interact with the menu, objects defined with a pin
Button *buttonUp = new Button(10);
Button *buttonEnter = new Button(11);
Button *buttonDown = new Button(12);

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

// initialize the library variables by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 13, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// make a display object (constructor defined in Display.h)
Display *LCD = new Display();


//////////////////////////
//  Internal Variables  //
//////////////////////////
// sensor pins
int s0pin = A0;
int s1pin = A1;
int s2pin = A2;

// motor pins
int m0pin = 5;
int m1pin = 6;

// display
bool displayOn = false;

// for watering
bool wateringNecessary = false;
long wateringStart = 0;


// Ultrasonic sensor
int trigPin = 7;    // Trigger
int echoPin = 8;    // Echo
long duration, cm, volume;

// water tank (all in cm)
long tankWidth = 20;
long tankDepth = 20;
long tankHeight = 25;

long distFromSensor = 5; // magic number for distance between sensor and water surface

void setup() {
  Serial.begin(9600);
  Serial.println("\n");
  Serial.println(timestamp() + "Hello World!");
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  // first and second plant on display
  LCD->updatePlants(plants, 0, 1, pASize);
  LCD->updateCursor(0, plants, 0, 1, pASize);
  updateDisplay();

  // print plants to see if their data are alright
  printListOfPlants();
  lcd.display();
  Serial.println(timestamp() + "LCD have been printed/displayed");

  // initiate pins for sensors and motor
  pinInit();
  Serial.println(timestamp() + "pins initiated");
}



void loop() {
  // madeshift listeners
  bool tempDown = buttonDown->isItPressed();
  if(tempDown){
    // timestamp added to Serial print of action notification
    Serial.print(timestamp() + "Down pressed = ");
    Serial.println(String(tempDown));
    
    LCD->scrollDown(plants, pASize);
    updateDisplay();
  }
  bool tempEnter = buttonEnter->isItPressed();
  if(tempEnter){
    // timestamp added to Serial print of action notification
    Serial.print(timestamp() + "Enter pressed = ");
    Serial.println(String(tempEnter));
    
    toggleDisplay();
  }
  bool tempUp = buttonUp->isItPressed();
  if(tempUp){
    // timestamp added to Serial print of action notification
    Serial.print(timestamp() + "Up pressed = ");
    Serial.println(String(tempUp));
    
    LCD->scrollUp(plants, pASize);
    updateDisplay();
  }
  
}



////////////////////////
// Internal Functions //
////////////////////////

// sets text on top and bottom row of LCD to text Strings sat in Display.h
void updateDisplay(){
  lcd.clear();
  
  lcd.setCursor(0, 0); // where to pring
  lcd.print(LCD->getTopTxt()); // print the text from Display.h
  Serial.println(timestamp() + "top text: " + LCD->getTopTxt());
  
  lcd.setCursor(0, 1); // where to pring
  lcd.print(LCD->getBotTxt()); // print the text from Display.h
  Serial.println(timestamp() + "bot text: " + LCD->getBotTxt());
}

// turn display on or off. 
// Always inverse of the current state
void toggleDisplay(){
  if(displayOn) {
    lcd.noDisplay();
    displayOn = false;
  } else {
    lcd.display();
    displayOn = true;
  }
}

// make serial print of plants list with their attributes
void printListOfPlants(){
  Serial.println("\nList contains these " + String(pASize) + " plants:");
  for(int i = 0; i < pASize; i++){
    Serial.println("Name: " + String(plants[i]->getName()) + ", ");
    Serial.println("Min moist: " + String(plants[i]->getMinMoist()) + "%, ");
    Serial.println("Max moist: " + String(plants[i]->getMaxMoist()) + "%, ");
    Serial.println("Prefered direct light: " + String(plants[i]->getDirLight()) + " min,");
    Serial.println("Prefered indirect light: " + String(plants[i]->getIndLight()) + " min \n");
  }
}

// timestamp for the Serial.print() in format "hours:minutes:seconds:milliseconds"
String timestamp(){
  long milliSec = millis();
  long tempSec = milliSec/1000;
  long tempMin = (tempSec/60);
  long tempHour = (tempMin/60);
  
  return(String(tempHour%24) + ":"
       + String(tempMin%60) + ":"
       + String(tempSec%60) + ":"
       + String(milliSec - ((milliSec/1000)*1000)) + " - ");
}





// -------------------------------------------------------------------------------------------------------------------------- //

/////////////////
// IN PROGRESS //
/////////////////

// to initiate pins
void pinInit(){
  // sensor pins set to INPUT by function in Button class
  buttonUp->init();
  buttonEnter->init();
  buttonDown->init();
  
  // motor pins
  pinMode(m0pin, OUTPUT);
  pinMode(m1pin, OUTPUT);

  // ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

// read a sensor (necessary with a function for this?)
long sensorRead(int pin){
  return(analogRead(pin));
}

long readWaterlevel(){
  // sensor is triggered by a HIGH pulse of 10 or more microseconds
  // short LOW pulse beforehand to ensure clean HIGH pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // divided by 29.1 or multiplied by 0.0343

  // then convert into volume
  

  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
}


// give plant a specific amount of water (hmm, maybe this isn't the smartest thing though)
void waterPlant(bool necessary, int amount/*[cl]*/){
  if(necessary){
    wateringStart = millis();
    digitalWrite(m0pin, HIGH);
    wateringNecessary = false;
  }
}

// calculates duration of motor activity necessary for watering
long waterAmountToWateringDuration(int amount/*[cl]*/){
  // math plz
}
