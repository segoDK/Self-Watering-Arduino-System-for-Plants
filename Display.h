#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include "Plant.h"

  class Display {  
  private: 
  
  public:
    // variables for lcd display
    String topTxt; int topTxtLenght; long topPlantNum; 
    String botTxt; int botTxtLenght; long botPlantNum;
    int cursorLocation;
    String cursorIcon;
    Plant plants[];
    int arraySize;
    
    Display() {
      this->topTxt = "";
      this->topTxtLenght = 0;
      this->topPlantNum = 0;
      this->botTxt = "";
      this->botTxtLenght = 0;
      this->botPlantNum = 0;
      this->cursorLocation = 0;
      this->cursorIcon = "<--";
      this->arraySize = 0;
    }

    void updatePlants(Plant *internalPlants[], int topPlant, int botPlant, int arraySize);
    void updateTxt(String topText, String botText, int topPlant, int botPlant);
    void updateCursor(int line, Plant *internalPlants[], int topPlant, int botPlant, int arraySize);
    
    void scrollDown(Plant *internalPlants[], int arraySize);
    void scrollUp(Plant *internalPlants[], int arraySize);
    
    String getTopTxt();
    String getBotTxt();

    void addPlant(Plant plant);
    
  }; // don't forget the semicolon at the end of the class

#endif
