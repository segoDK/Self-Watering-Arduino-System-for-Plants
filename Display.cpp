#include "Arduino.h"
#include "Display.h"
#include "Plant.h" 

// update the two lines of text with two plants
void Display::updatePlants(Plant internalPlants[], int topPlant, int botPlant, int arraySize){
  this->arraySize    = arraySize;
  this->topPlantNum  = topPlant;
  this->botPlantNum  = botPlant; 
  this->topTxt       = internalPlants[topPlant].getName();
  this->topTxtLenght = this->topTxt.length();
  this->botTxt       = internalPlants[botPlant].getName();
  this->botTxtLenght = this->botTxt.length();
}
// update the two lines of text with two text strings
void Display::updateTxt(String topText, String botText, int topPlant, int botPlant){
  this->topPlantNum  = topPlant; 
  this->botPlantNum  = botPlant; 
  this->topTxt       = topText;
  this->topTxtLenght = topText.length();
  this->botTxt       = botText;
  this->botTxtLenght = botText.length();
}
// set the cursor at a specific line
void Display::updateCursor(int line){
  if(line = 0){
    this->updateTxt(this->topTxt + this->cursorIcon, this->botTxt, this->topPlantNum, this->botPlantNum);
    cursorLocation = line; // placed here so it isn't changed on error
  } else if(line = 1){
    this->updateTxt(this->topTxt, this->botTxt + this->cursorIcon, this->topPlantNum, this->botPlantNum);
    cursorLocation = line;
  } else { 
    Serial.println("ERROR in Display.updateCursor()"); 
  }
}

// scroll down in teh displayed plants
void Display::scrollDown(Plant *internalPlants, int arraySize){
  if(cursorLocation=0) {
    this->updateCursor(1);
  } else if(this->cursorLocation=1) {
    if(this->botPlantNum < 5){
      this->updatePlants(internalPlants, this->topPlantNum++, this->botPlantNum++, arraySize);
    }
  } else {
    Serial.println("ERROR in Display.scrollDown()");
  }
}
// scroll up in the displayed plants
void Display::scrollUp(Plant *internalPlants, int arraySize){
  if(cursorLocation=1) {
    this->updateCursor(0);
  } else if(cursorLocation=0) {
    if(this->topPlantNum > 0){
      this->updatePlants(internalPlants, this->topPlantNum--, this->botPlantNum--, arraySize);
    }
  } else {
    Serial.println("ERROR in Display.scrollUp()");
  }
}

String Display::getTopTxt(){
  return(this->topTxt);
}
String Display::getBotTxt(){
  return(this->botTxt);
}

void Display::addPlant(Plant plant){
  int arraySize = sizeof(this->plants)/2; // whole size divided by size of a char
  
  this->plants[arraySize] = plant;
  Serial.println(plant.getName() + " added to Display's list");
  Serial.println("with min moist: " + String(plant.getMinMoist()));
}
