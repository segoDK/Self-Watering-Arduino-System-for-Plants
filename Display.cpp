#include "Arduino.h"
#include "Display.h"
#include "Plant.h" 

// update the two lines of text with two plants
void Display::updatePlants(Plant* internalPlants[], int topPlant, int botPlant, int arraySize){
  this->arraySize    = arraySize;
  this->topPlantNum  = topPlant;
  this->botPlantNum  = botPlant; 
  this->topTxt       = internalPlants[this->topPlantNum]->getName();
  this->topTxtLenght = this->topTxt.length();
  this->botTxt       = internalPlants[this->botPlantNum]->getName();
  this->botTxtLenght = this->botTxt.length();
  
  /*
  Serial.println("\nIn Display.h, list contains these " + String(arraySize) + " plants:");
  for(int i = 0; i < arraySize; i++){
    Serial.println("Name: " + String(internalPlants[i]->getName()) + ", ");
    Serial.println("Min moist: " + String(internalPlants[i]->getMinMoist()) + "%, ");
    Serial.println("Max moist: " + String(internalPlants[i]->getMaxMoist()) + "%, ");
    Serial.println("Prefered direct light: " + String(internalPlants[i]->getDirLight()) + " min,");
    Serial.println("Prefered indirect light: " + String(internalPlants[i]->getIndLight()) + " min \n");
  }
  */
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
void Display::updateCursor(int line, Plant* internalPlants[], int topPlant, int botPlant, int arraySize){
  if(line == 0){
    this->updateTxt(String(internalPlants[topPlant]->getName() + " " + this->cursorIcon), internalPlants[botPlant]->getName(), topPlant, botPlant);
    this->cursorLocation = line; // placed here so it isn't changed on error
    Serial.println(" - cursor location sat to: " + String(cursorLocation) + ". Txt says: " + this->topTxt);
  } else if(line == 1){
    this->updateTxt(internalPlants[topPlant]->getName(), String(internalPlants[botPlant]->getName() + " " + this->cursorIcon), topPlant, botPlant);
    this->cursorLocation = line; // -||- also
    Serial.println(" - cursor location sat to: " + String(cursorLocation) + ". Txt says: " + this->botTxt);
  } else {
    Serial.println("!ERROR in Display.updateCursor()!"); 
  }
}

// scroll down in the displayed plants
// sets text Strings for top and bottom row which later can be extracted
void Display::scrollDown(Plant* internalPlants[], int arraySize){
  Serial.println(" - I should scroll down");
  if(cursorLocation == 0) {
    this->updateCursor(1, internalPlants, this->topPlantNum, this->botPlantNum, arraySize);
    Serial.println(" - cursor moves");
  } else if(this->cursorLocation == 1) {
    if(this->botPlantNum < arraySize-1){
      this->topPlantNum++;
      this->botPlantNum++;
      this->updatePlants(internalPlants, this->topPlantNum, this->botPlantNum, arraySize);
      this->updateCursor(this->cursorLocation, internalPlants, this->topPlantNum, this->botPlantNum, arraySize);
    }
    Serial.println(" - going to plant " + String(this->botPlantNum) + "/" + String(arraySize));
  } else {
    Serial.println("!ERROR in Display.scrollDown()!");
  }
}
// scroll up in the displayed plants
// sets text Strings for top and bottom row which later can be extracted
void Display::scrollUp(Plant* internalPlants[], int arraySize){
  Serial.println(" - I should scroll up");
  if(cursorLocation == 1) {
    this->updateCursor(0, internalPlants, this->topPlantNum, this->botPlantNum, arraySize);
    Serial.println(" - cursor moves");
  } else if(cursorLocation == 0) {
    if(this->topPlantNum >= 1){
      this->botPlantNum--;
      this->topPlantNum--;
      this->updatePlants(internalPlants, this->topPlantNum, this->botPlantNum, arraySize);
      this->updateCursor(this->cursorLocation, internalPlants, this->topPlantNum, this->botPlantNum, arraySize);
    }
    Serial.println(" - going to plant " + String(this->botPlantNum) + "/" + String(arraySize));
  } else {
    Serial.println("!ERROR in Display.scrollUp()!");
  }
}

// to get text for top and bottom row on LCD out of library and into Main
String Display::getTopTxt(){
  return(this->topTxt);
}
String Display::getBotTxt(){
  return(this->botTxt);
}

// should propably not be used
void Display::addPlant(Plant plant){
  int arraySize = sizeof(this->plants)/2; // whole size divided by size of a char
  
  this->plants[arraySize] = plant;
  Serial.println(" - " + plant.getName() + " added to Display's list");
  Serial.println(" - with min moist: " + String(plant.getMinMoist()));
}
